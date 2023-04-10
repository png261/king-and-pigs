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
    , m_bDoorIn(false)
    , m_bWantDoorIn(false)
{}

Player::~Player() {}

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
    m_animations[ATTACK] = std::make_unique<Animation>("player attack", 78, 58, 3, false);
    m_animations[HIT] = std::make_unique<Animation>("player hit", 78, 58, 2);
    m_animations[DYING] = std::make_unique<Animation>("player dead", 78, 58, 4, false);
    m_animations[DOOR_IN] = std::make_unique<Animation>("player door in", 78, 58, 8, false);
    m_animations[DOOR_OUT] = std::make_unique<Animation>("player door out", 78, 58, 8, false);

    doorOutTimer.setTime(300);
    m_curAnimation = DOOR_OUT;
    m_animations[m_curAnimation]->start();
    doorOutTimer.start();
}

void Player::update()
{
    if (isDead()) {
        GameStateMachine::Instance().pushState(std::make_shared<LoseState>());
        return;
    }

    GameObject::update();
    handleInput();

    m_raycast.clear();
    float nray = 50;
    for (int i = 0; i < nray; ++i) {
        b2Vec2 start = getPosition() + m_direction * (b2Vec2(m_width / 2.0f, 0)) +
                       b2Vec2(0, -m_height / 2.0f + i * m_height / nray);
        b2Vec2 end = start + m_direction * b2Vec2(m_visionRange, 0);
        m_raycast.push_back({start, end});
    }

    VisionObject::update();

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

    DamageableObject::update();
    AttackerObject::update();
    updateAnimation();
    handleSound();
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
    if (isDead()) {
        return;
    }

    if (isDying()) {
        return;
    }

    if (isInvulnerable()) {
        return;
    }

    if (m_bDoorIn) {
        m_bWantDoorIn = true;
        return;
    }

    InputHandler& input = InputHandler::Instance();

    if (isOnGround()) {
        m_bWantDoorIn = input.isKeyDown(KEY_W);

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

    if (input.isKeyPressed(KEY_A)) {
        attack();
        SoundManager::Instance().playSFX("player attack");
    }

    m_bFlipped = m_direction == LEFT;
};

void Player::updateAnimation()
{
    if (m_bDoorIn) {
        return;
    }

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

    if (doorOutTimer.isDone()) {
        if (newAnimation != m_curAnimation) {
            m_animations[m_curAnimation]->stop();
            m_curAnimation = newAnimation;
            m_animations[m_curAnimation]->start();
        }
    }
}

void Player::doorIn()
{
    m_bDoorIn = true;
    m_curAnimation = DOOR_IN;
    m_animations[m_curAnimation]->start();
}

void Player::doorOut()
{
    m_curAnimation = DOOR_OUT;
    m_animations[m_curAnimation]->start();
}

bool Player::isWantDoorIn()
{
    return m_bWantDoorIn;
}

bool Player::isDoorIn()
{
    return m_bDoorIn;
}
