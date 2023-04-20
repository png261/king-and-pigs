#include "Player.hpp"

#include <memory>

#include "Animation.hpp"
#include "AttackerObject.hpp"
#include "Camera.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "LoseState.hpp"
#include "PhysicWorld.hpp"
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
    setFilterData(PhysicWorld::CAT_PLAYER, PhysicWorld::MASK_PLAYER);

    createCircleSensor(
        -b2Vec2((width_ * 0.5 + attack_range_) * 0.5, 0),
        attack_range_,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PLAYER_ATTACK_SENSOR);

    createCircleSensor(
        b2Vec2((width_ * 0.5 + attack_range_) * 0.5, 0),
        attack_range_,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PLAYER_ATTACK_SENSOR);

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

    leavingDoorTimer.setTime(300);
    current_animation_ = LEAVING_DOOR;
    animations_[current_animation_]->start();
    leavingDoorTimer.start();
}

void Player::update()
{
    if (isDead()) {
        GameStateMachine::Instance().pushState(std::make_unique<LoseState>());
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
    float nray = 50;
    for (int i = 0; i < nray; ++i) {
        b2Vec2 start = getPosition() + direction_ * (b2Vec2(width_ / 2.0f, 0)) +
                       b2Vec2(0, -height_ / 2.0f + i * height_ / nray);
        b2Vec2 end = start + direction_ * b2Vec2(vision_range_, 0);
        raycast_.push_back({start, end});
    }

    if (isSeeing(PhysicWorld::CAT_WALL) && vision_nearest_distance_ < 1) {
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

void Player::draw()
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

    InputHandler& input = InputHandler::Instance();

    if (isOnGround()) {
        is_want_enter_door_ = input.isKeyDown(KEY_W);

        if (input.isKeyPressed(KEY_SPACE)) {
            jump();
            SoundManager::Instance().playSFX("player_jump");
        }
    }

    if (input.isKeyPressed(KEY_RIGHT)) {
        moveRight();
        direction_ = RIGHT;
    }
    if (input.isKeyPressed(KEY_LEFT)) {
        moveLeft();
        direction_ = LEFT;
    }

    if (input.isKeyDown(KEY_A)) {
        attack();
        SoundManager::Instance().playSFX("player_attack");
    }

    is_flipped_ = direction_ == LEFT;
};

void Player::updateAnimation()
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

    if (isEnteringDoor()) {
        newAnimation = ENTERING_DOOR;
    }

    if (leavingDoorTimer.isDone()) {
        if (newAnimation != current_animation_) {
            animations_[current_animation_]->stop();
            current_animation_ = newAnimation;
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

bool Player::isWantEnterDoor()
{
    return is_want_enter_door_;
}

bool Player::isEnteringDoor()
{
    return is_entering_door_;
}
