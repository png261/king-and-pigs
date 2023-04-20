#include "Pig.hpp"

#include "DamageableObject.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"
#include "SoundManager.hpp"

Pig::Pig()
    : GameObject()
    , VisionObject(100)
    , DamageableObject(3, 300, 500)
    , AttackerObject(1, 20, 500)
{}

void Pig::load(std::unique_ptr<LoaderParams> const& params)
{
    GameObject::load(std::move(params));
    createBody(params->x(), params->y(), width_, height_);
    setFilterData(PhysicWorld::CAT_PIG, PhysicWorld::MASK_PIG);
    fixture_->SetDensity(50);

    createCircleSensor(
        -b2Vec2((width_ * 0.5 + attack_range_) * 0.5, 0),
        attack_range_,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    createCircleSensor(
        b2Vec2((width_ * 0.5 + attack_range_) * 0.5, 0),
        attack_range_,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

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
        disappear();
        return;
    }

    GameObject::update();
    raycast_.clear();
    float nray = 50;
    for (int i = 0; i < nray; ++i) {
        b2Vec2 start = getPosition() + direction_ * (b2Vec2(width_ / 2.0f, 0)) +
                       b2Vec2(0, -height_ / 2.0f + i * height_ / nray);
        b2Vec2 end = start + direction_ * b2Vec2(vision_range_, 0);
        raycast_.push_back({start, end});
    }

    VisionObject::update();
    VisionObject::update();
    handleMovement();
    is_flipped_ = direction_ == RIGHT;

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

    if (isSeeing(PhysicWorld::CAT_PLAYER)) {
        seeingPlayer();
    }
    if (isSeeing(PhysicWorld::CAT_WALL)) {
        seeingWall();
    }
    if (isSeeing(PhysicWorld::CAT_BOX)) {
        seeingBox();
    }
    if (isSeeing(PhysicWorld::CAT_PIG)) {
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
    int newAnimation = current_animation_;

    if (isOnGround()) {
        if (current_animation_ == FALL) {
            newAnimation = GROUND;
        } else {
            newAnimation = IDLE;
        }
        if (isRunning()) {
            newAnimation = RUN;
        }
    } else {
        if (getBody()->GetLinearVelocity().y < 0) {
            newAnimation = JUMP;
        } else {
            newAnimation = FALL;
        }
    }

    if (isDying()) {
        newAnimation = DYING;
    } else if (isInvulnerable()) {
        newAnimation = HIT;
    } else if (isAttack()) {
        newAnimation = ATTACK;
    }

    if (newAnimation != current_animation_) {
        current_animation_ = newAnimation;
        animations_[current_animation_]->start();
    }
}

void Pig::draw()
{
    GameObject::draw();
    VisionObject::debugDraw();
}
