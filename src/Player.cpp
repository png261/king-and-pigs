#include "Player.hpp"

#include <memory>

#include "Animation.hpp"
#include "AttackerObject.hpp"
#include "Camera.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "Log.hpp"
#include "LoseState.hpp"
#include "PhysicManager.hpp"
#include "SoundManager.hpp"
#include "VisionObject.hpp"

Player::Player()
    : GameObject()
    , VisionObject(32.0f)
    , DamageableObject(3, 300, 300)
    , AttackerObject(1, 20, 300)
    , is_entering_door_(false)
    , is_want_enter_door_(false)
{}

void Player::load(std::unique_ptr<LoaderParams> const& params)
{
    GameObject::load(std::move(params));
    createBody(params->x(), params->y(), width_, height_);
    setFilterData(ContactCategory::CAT_PLAYER, ContactMask::MASK_PLAYER);

    createCircleSensor(
        -b2Vec2((width_ * 0.5 + attack_range_) * 0.5, 0),
        attack_range_,
        ContactCategory::CAT_ATTACK_SENSOR,
        ContactMask::MASK_PLAYER_ATTACK_SENSOR);

    createCircleSensor(
        b2Vec2((width_ * 0.5 + attack_range_) * 0.5, 0),
        attack_range_,
        ContactCategory::CAT_ATTACK_SENSOR,
        ContactMask::MASK_PLAYER_ATTACK_SENSOR);

    move_speed_ = 90;
    jump_height_ = 32.0f;
    direction_ = RIGHT;

    loadAnimation();
}

void Player::loadAnimation()
{
    animations_[IDLE] = std::make_unique<Animation>("player_idle", 78, 58, 11);
    animations_[RUN] = std::make_unique<Animation>("player_run", 78, 58, 8);
    animations_[JUMP] = std::make_unique<Animation>("player_jump", 78, 58, 1);
    animations_[FALL] = std::make_unique<Animation>("player_fall", 78, 58, 1);
    animations_[GROUND] = std::make_unique<Animation>("player_ground", 78, 58, 1);
    animations_[ATTACK] = std::make_unique<Animation>("player_attack", 78, 58, 3);
    animations_[HIT] = std::make_unique<Animation>("player_hit", 78, 58, 2);
    animations_[DYING] = std::make_unique<Animation>("player_dead", 78, 58, 4, false);
    animations_[ENTERING_DOOR] =
        std::make_unique<Animation>("player_entering_door", 78, 58, 8, false);
    animations_[LEAVING_DOOR] =
        std::make_unique<Animation>("player_leaving_door", 78, 58, 8, false);

    leaving_door_timer_.setTime(300);
    current_animation_ = LEAVING_DOOR;
    animations_[current_animation_]->start();
    leaving_door_timer_.start();
}

void Player::update()
{
    if (isDead()) {
        GameStateManager::Instance().pushState(std::make_unique<LoseState>());
        return;
    }

    GameObject::update();
    VisionObject::update();
    DamageableObject::update();
    AttackerObject::update();
    handleInput();
    handleVision();
    handleSound();
    updateAnimation();
}

void Player::handleVision()
{
    raycast_.clear();
    float num_ray = 50.0f;
    for (int i = 0; i < num_ray; ++i) {
        b2Vec2 start = getPosition() + direction_ * (b2Vec2(width_ * 0.5f, 0)) +
                       b2Vec2(0, -height_ * 0.5f + i * height_ / num_ray);
        b2Vec2 end = start + direction_ * b2Vec2(vision_range_, 0);
        raycast_.push_back({start, end});
    }

    if (isSeeing(ContactCategory::CAT_WALL) && vision_nearest_distance_ < 1) {
        if (direction_ == RIGHT) {
            setMoveRight(false);
        } else {
            setMoveLeft(false);
        }
    } else {
        setMoveRight(true);
        setMoveLeft(true);
    }
}

void Player::draw() const
{
    if (isDead()) {
        return;
    }

    GameObject::draw();
    VisionObject::debugDraw();
}

void Player::handleSound()
{
    if (isDying()) {
        SoundManager::Instance().playSFX("player_dying");
    }
    if (isAttack()) {
        SoundManager::Instance().playSFX("player_attack");
    }
}

void Player::handleInput()
{
    if (isDead() || isDying() || isInvulnerable() || isEnteringDoor()) {
        return;
    }

    InputManager& input = InputManager::Instance();

    if (isOnGround()) {
        is_want_enter_door_ = input.isKeyDown(KEY_W);

        if (input.isKeyPressed(KEY_K)) {
            jump();
            SoundManager::Instance().playSFX("player_jump");
        }
    }
    if (input.isKeyPressed(KEY_D)) {
        moveRight();
        direction_ = RIGHT;
    }
    if (input.isKeyPressed(KEY_A)) {
        moveLeft();
        direction_ = LEFT;
    }

    if (input.isKeyPressed(KEY_J)) {
        attack();
        SoundManager::Instance().playSFX("player_attack");
    }

    is_flip_ = direction_ == LEFT;
};

void Player::updateAnimation()
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

    if (isEnteringDoor()) {
        new_animation = ENTERING_DOOR;
    }

    if (leaving_door_timer_.isDone()) {
        if (new_animation != current_animation_) {
            animations_[current_animation_]->stop();
            current_animation_ = new_animation;
            animations_[current_animation_]->start();
        }
    }
}

void Player::enterDoor()
{
    is_entering_door_ = true;
}

void Player::leavingDoor()
{
    current_animation_ = LEAVING_DOOR;
    animations_[current_animation_]->start();
}

bool Player::isWantEnterDoor() const
{
    return is_want_enter_door_;
}

bool Player::isEnteringDoor() const
{
    return is_entering_door_;
}
