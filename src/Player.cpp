#include <iostream>
#include "Animation.hpp"
#include "AttackableObject.hpp"
#include "Box2D.hpp"
#include "Camera.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"

Player::Player()
    : GameObject()
    , DamageableObject(3, 300)
    , AttackableObject(1, 50, 300)
    , m_bDoorIn(false)
{}

void Player::load(const LoaderParams* const pParams)
{
    GameObject::load(pParams);
    m_moveSpeed = 100;
    m_jumpHeight = 20.0f;

    b2Filter filter;
    filter.categoryBits = Box2D::CAT_PLAYER;
    filter.maskBits = Box2D::MASK_PLAYER;
    m_pFixture->SetFilterData(filter);

    this->createAttackSensor(getBody(), m_width, Box2D::MASK_PLAYER_ATTACK_SENSOR);
    this->loadAnimation();

    m_currentState = ON_GROUND;
    m_currentAttackState = ON_NORMAL;
}

void Player::loadAnimation()
{
    m_animations[Animation::IDLE] = new Animation("player idle", 78, 58, 11);
    m_animations[Animation::RUN] = new Animation("player run", 78, 58, 8);
    m_animations[Animation::JUMP] = new Animation("player jump", 78, 58, 1);
    m_animations[Animation::FALL] = new Animation("player fall", 78, 58, 1);
    m_animations[Animation::GROUND] = new Animation("player ground", 78, 58, 1);
    m_animations[Animation::ATTACK] = new Animation("player attack", 78, 58, 3, false);
    m_animations[Animation::HIT] = new Animation("player hit", 78, 58, 2);
    m_animations[Animation::DEAD] = new Animation("player dead", 78, 58, 4, false);
    m_animations[Animation::DOOR_IN] = new Animation("player door in", 78, 58, 8, false);
    m_animations[Animation::DOOR_OUT] = new Animation("player door out", 78, 58, 8, false);

    m_curAnimation = Animation::DOOR_OUT;
    m_animations[m_curAnimation]->start();
    doorOutTimer.start();
}

void Player::update()
{
    this->handleInput();
    GameObject::update();
    DamageableObject::update();
    AttackableObject::update();
    this->updateAnimation();
}

void Player::handleInput()
{
    if (m_bDoorIn) {
        return;
    }

    InputHandler* const input = InputHandler::Instance();

    if (m_currentState == ON_GROUND) {
        if (input->isKeyPressed(KEY_W)) {
            m_bWantDoorIn = true;
        }
        if (input->isKeyPressed(KEY_SPACE)) {
            this->jump();
        }
        if (input->isKeyPressed(KEY_RIGHT)) {
            this->moveRight();
            m_bTurnRight = true;
        }
        if (input->isKeyPressed(KEY_LEFT)) {
            this->moveLeft();
            m_bTurnRight = false;
        }
    }

    if (m_currentAttackState == ON_NORMAL) {
        if (input->isKeyPressed(KEY_A)) {
            this->attack();
        }
    }
};

void Player::updateAnimation()
{
    if (m_bDoorIn) {
        return;
    }

    Animation::AnimationID newAnimation = m_curAnimation;

    if (this->isInvulnerable()) {
        m_currentAttackState = ON_HIT;
    } else if (this->isAttack()) {
        m_currentAttackState = ON_ATTACK;
    } else if (this->isDead()) {
        m_currentAttackState = ON_DIE;
    } else {
        m_currentAttackState = ON_NORMAL;
    }

    switch (m_currentState) {
    case ON_GROUND:
        if (InputHandler::Instance()->isKeyPressed(KEY_LEFT)) {
            newAnimation = Animation::RUN;
        } else if (InputHandler::Instance()->isKeyPressed(KEY_RIGHT)) {
            newAnimation = Animation::RUN;
        } else {
            newAnimation = Animation::IDLE;
        }
        break;
    case ON_FLY:
        if (this->getBody()->GetLinearVelocity().y == 0) {
            m_currentState = ON_GROUND;
            break;
        }

        if (this->getBody()->GetLinearVelocity().y < 0) {
            newAnimation = Animation::JUMP;
        } else {
            newAnimation = Animation::FALL;
        }

        break;
    }

    switch (m_currentAttackState) {
    case ON_NORMAL:
        break;
    case ON_HIT:
        newAnimation = Animation::HIT;
        break;
    case ON_ATTACK:
        newAnimation = Animation::ATTACK;
        break;
    case ON_DIE:
        newAnimation = Animation::DEAD;
        break;
    }

    if (doorOutTimer.delta() > 1000) {
        doorOutTimer.stop();
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
    m_curAnimation = Animation::DOOR_IN;
    m_animations[m_curAnimation]->start();
}

void Player::doorOut()
{
    m_bDoorIn = true;
    m_curAnimation = Animation::DOOR_OUT;
    m_animations[m_curAnimation]->start();
}

bool Player::isWantDoorIn()
{
    return m_bWantDoorIn;
}
