#include "Pig.hpp"

#include "Camera.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "PhysicManager.hpp"
#include "Shapes.hpp"
#include "SoundManager.hpp"

Pig::Pig()
    : GameObject()
    , VisionObject(100)
    , DamageableObject(2, 300, 700)
    , AttackerObject(1, 20, 500)
{}

void Pig::load(std::unique_ptr<LoaderParams> const& params)
{
    GameObject::load(std::move(params));
    createBody(params->x(), params->y(), width_, height_);

    createRectangleFixture(
        {0, 0},
        width_,
        height_,
        ContactCategory::CAT_PIG,
        ContactMask::MASK_PIG);

    createRectangleSensor(
        b2Vec2(0, height_ * 0.5),
        width_ - 0.5,
        1,
        ContactCategory::CAT_FOOT_SENSOR,
        ContactMask::MASK_FOOT_SENSOR);

    createCircleSensor(
        -b2Vec2((width_ * 0.5 + attack_range_) * 0.5, 0),
        attack_range_,
        ContactCategory::CAT_ATTACK_SENSOR,
        ContactMask::MASK_PIG_ATTACK_SENSOR);

    createCircleSensor(
        b2Vec2((width_ * 0.5 + attack_range_) * 0.5, 0),
        attack_range_,
        ContactCategory::CAT_ATTACK_SENSOR,
        ContactMask::MASK_PIG_ATTACK_SENSOR);

    move_speed_ = 40;
    jump_height_ = 32.0f;
    direction_ = LEFT;

    loadAnimation();
}

void Pig::loadAnimation()
{
    animations_[IDLE] = std::make_unique<Animation>("pig_idle", 34, 28, 11);
    animations_[RUN] = std::make_unique<Animation>("pig_run", 34, 28, 6);
    animations_[JUMP] = std::make_unique<Animation>("pig_jump", 34, 28, 1);
    animations_[FALL] = std::make_unique<Animation>("pig_fall", 34, 28, 1);
    animations_[GROUND] = std::make_unique<Animation>("pig_ground", 34, 28, 1);
    animations_[ATTACK] = std::make_unique<Animation>("pig_attack", 34, 28, 5);
    animations_[HIT] = std::make_unique<Animation>("pig_hit", 34, 28, 2);
    animations_[DYING] = std::make_unique<Animation>("pig_dead", 34, 28, 4, false);

    current_animation_ = IDLE;
    animations_[current_animation_]->start();
}

void Pig::update()
{
    if (isDead()) {
        Game::Instance().addScore(10);
        disappear();
        return;
    }

    GameObject::update();
    raycast_.clear();
    const float nray = 50;
    for (int i = 0; i < nray; ++i) {
        const b2Vec2 start = getPosition() + direction_ * (b2Vec2(width_ * 0.5f, 0)) +
                       b2Vec2(0, -height_ * 0.5f + i * height_ / nray);
        const b2Vec2 end = start + direction_ * b2Vec2(vision_range_, 0);
        raycast_.push_back({start, end});
    }

    VisionObject::update();
    VisionObject::update();
    handleMovement();
    is_flip_ = direction_ == RIGHT;

    DamageableObject::update();
    AttackerObject::update();
    updateAnimation();
    handleSound();
}

void Pig::handleSound()
{
    if (isDying()) {
        SoundManager::Instance().playSFX("pig_dying");
    }

    if (isAttack()) {
        SoundManager::Instance().playSFX("pig_attack");
    }
}

void Pig::handleMovement()
{
    if (isDying()) {
        return;
    }

    if (direction_ == RIGHT) {
        moveRight();
    } else {
        moveLeft();
    }

    if (isSeeing(ContactCategory::CAT_PLAYER)) {
        seeingPlayer();
    }
    if (isSeeing(ContactCategory::CAT_WALL)) {
        seeingWall();
    }
    if (isSeeing(ContactCategory::CAT_BOX)) {
        seeingBox();
    }
    if (isSeeing(ContactCategory::CAT_PIG)) {
        seeingPig();
    }
}

void Pig::seeingPlayer()
{
    if (vision_nearest_distance_ >= attack_range_) {
        return;
    }
    if (canAttack()) {
        attack();
    }
}

void Pig::changeDirection()
{
    if (direction_ == RIGHT) {
        setMoveRight(false);
        setMoveLeft(true);
        direction_ = LEFT;
    } else {
        setMoveLeft(false);
        setMoveRight(true);
        direction_ = RIGHT;
    }
}
void Pig::seeingWall()
{
    if (vision_nearest_distance_ >= 1) {
        return;
    }
    changeDirection();
}

void Pig::seeingBox()
{
    if (vision_nearest_distance_ >= 10) {
        return;
    }
    if (isDisableJump()) {
        changeDirection();
    } else {
        jump();
    }
}

void Pig::seeingPig()
{
    if (vision_nearest_distance_ >= 10) {
        return;
    }

    changeDirection();
}

void Pig::updateAnimation()
{
    int new_animation = current_animation_;

    if (isOnGround()) {
        if (current_animation_ == FALL) {
            new_animation = GROUND;
        } else {
            new_animation = IDLE;
        }
        if (isRunning()) {
            new_animation = RUN;
        }
    } else {
        if (getBody()->GetLinearVelocity().y < 0) {
            new_animation = JUMP;
        } else {
            new_animation = FALL;
        }
    }

    if (isDying()) {
        new_animation = DYING;
    } else if (isInvulnerable()) {
        new_animation = HIT;
    } else if (isAttack()) {
        new_animation = ATTACK;
    }

    if (new_animation != current_animation_) {
        current_animation_ = new_animation;
        animations_[current_animation_]->start();
    }
}

void Pig::draw() const
{
    GameObject::draw();
    VisionObject::debugDraw();
    drawHealthBar();
}

void Pig::drawHealthBar() const
{
    const int kWidth = getMaxHp() * 10;
    const int kHeight = 2;

    const b2Vec2 position = {
        (getX() - getWidth() * 0.5f - Camera::Instance().getX()) * Camera::Instance().getZoom(),
        (getY() - getHeight() * 0.5f - Camera::Instance().getY()) * Camera::Instance().getZoom()};

    Rectangle bar{
        position.x,
        position.y,
        static_cast<int>(kWidth * Camera::Instance().getZoom()),
        static_cast<int>(kHeight * Camera::Instance().getZoom())};

    const float currentHpWidth = kWidth * ((float)getHp() / getMaxHp());

    Rectangle status{
        position.x,
        position.y,
        static_cast<int>(currentHpWidth * Camera::Instance().getZoom()),
        static_cast<int>(kHeight * Camera::Instance().getZoom())};

    Game::Instance().getWindow()->drawBox(bar, 2, ColorName::GRAY);
    Game::Instance().getWindow()->drawBox(status, 2, ColorName::GREEN);
}
