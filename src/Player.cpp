#include "Player.hpp"

#include <iostream>
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
    , DamageableObject(3, 300, 500)
    , AttackerObject(1, 20, 300)
    , m_bEnteringDoor(false)
    , m_bWantEnterDoor(false)
{}

void Player::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    createBody(pParams->x(), pParams->y(), m_width, m_height);
    setFilterData(PhysicWorld::CAT_PLAYER, PhysicWorld::MASK_PLAYER);

    createCircleSensor(
        -b2Vec2((m_width * 0.5 + m_attackRange) * 0.5, 0),
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PLAYER_ATTACK_SENSOR);

    createCircleSensor(
        b2Vec2((m_width * 0.5 + m_attackRange) * 0.5, 0),
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PLAYER_ATTACK_SENSOR);

    m_moveSpeed = 90;
    m_jumpHeight = 32.0f;
    m_direction = RIGHT;

    loadAnimation();
}

void Player::loadAnimation()
{
    m_animations[IDLE] = std::make_unique<Animation>("player idle", 78, 58, 11);
    m_animations[RUN] = std::make_unique<Animation>("player run", 78, 58, 8);
    m_animations[JUMP] = std::make_unique<Animation>("player jump", 78, 58, 1);
    m_animations[FALL] = std::make_unique<Animation>("player fall", 78, 58, 1);
    m_animations[GROUND] = std::make_unique<Animation>("player ground", 78, 58, 1);
    m_animations[ATTACK] = std::make_unique<Animation>("player attack", 78, 58, 3);
    m_animations[HIT] = std::make_unique<Animation>("player hit", 78, 58, 2);
    m_animations[DYING] = std::make_unique<Animation>("player dead", 78, 58, 4, false);
    m_animations[DOOR_IN] = std::make_unique<Animation>("player door in", 78, 58, 8, false);
    m_animations[DOOR_OUT] = std::make_unique<Animation>("player door out", 78, 58, 8, false);

    exitDoorTimer.setTime(300);
    m_curAnimation = DOOR_OUT;
    m_animations[m_curAnimation]->start();
    exitDoorTimer.start();
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
    m_raycast.clear();
    float nray = 50;
    for (int i = 0; i < nray; ++i) {
        b2Vec2 start = getPosition() + m_direction * (b2Vec2(m_width / 2.0f, 0)) +
                       b2Vec2(0, -m_height / 2.0f + i * m_height / nray);
        b2Vec2 end = start + m_direction * b2Vec2(m_visionRange, 0);
        m_raycast.push_back({start, end});
    }

    if (m_seeingCategory & PhysicWorld::CAT_WALL && m_visionNearestDistance < 1) {
        if (m_direction == RIGHT) {
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
        SoundManager::Instance().playSFX("player dying");
    }
    if (isAttack()) {
        SoundManager::Instance().playSFX("player attack");
    }
}

void Player::handleInput()
{
    if (isDead() || isDying() || isInvulnerable() || isEnteringDoor()) {
        return;
    }

    InputHandler& input = InputHandler::Instance();

    if (isOnGround()) {
        m_bWantEnterDoor = input.isKeyDown(KEY_W);

        if (input.isKeyPressed(KEY_SPACE)) {
            jump();
            SoundManager::Instance().playSFX("player jump");
        }
    }

    if (input.isKeyPressed(KEY_RIGHT)) {
        moveRight();
        m_direction = RIGHT;
    }
    if (input.isKeyPressed(KEY_LEFT)) {
        moveLeft();
        m_direction = LEFT;
    }

    if (input.isKeyDown(KEY_A)) {
        attack();
        SoundManager::Instance().playSFX("player attack");
    }

    m_bFlipped = m_direction == LEFT;
};

void Player::updateAnimation()
{
    int newAnimation = m_curAnimation;

    if (isOnGround()) {
        newAnimation = IDLE;
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
        newAnimation = DOOR_IN;
    }

    if (exitDoorTimer.isDone()) {
        if (newAnimation != m_curAnimation) {
            m_animations[m_curAnimation]->stop();
            m_curAnimation = newAnimation;
            m_animations[m_curAnimation]->start();
        }
    }
}

void Player::enterDoor()
{
    m_bEnteringDoor = true;
}

void Player::exitDoor()
{
    m_curAnimation = DOOR_OUT;
    m_animations[m_curAnimation]->start();
}

bool Player::isWantEnterDoor()
{
    return m_bWantEnterDoor;
}

bool Player::isEnteringDoor()
{
    return m_bEnteringDoor;
}
