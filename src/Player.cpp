#include <iostream>
#include "Animation.hpp"
#include "AttackableObject.hpp"
#include "Box2D.hpp"
#include "Camera.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "PlatformerObject.hpp"
#include "SoundManager.hpp"

Player::Player()
    : PlatformerObject()
    , DamageableObject(3, 300)
    , AttackableObject(1, 50, 300)
{}

void Player::load(const LoaderParams* pParams)
{
    m_moveSpeed = 6 * Box2D::PPM;
    m_jumpSpeed = -6 * Box2D::PPM;

    PlatformerObject::load(pParams);

    b2Filter filter;
    filter.categoryBits = Box2D::CAT_PLAYER;
    filter.maskBits = Box2D::MASK_PLAYER;
    m_pFixture->SetFilterData(filter);

    this->createAttackSensor(getBody(), m_width, Box2D::MASK_PLAYER_ATTACK_SENSOR);

    m_animations[IDLE] = new Animation("player idle", 11);
    m_animations[RUN] = new Animation("player run", 8);
    m_animations[JUMP] = new Animation("player jump", 1);
    m_animations[FALL] = new Animation("player fall", 1);
    m_animations[GROUND] = new Animation("player ground", 1);
    m_animations[ATTACK] = new Animation("player attack", 3, false);
    m_animations[HIT] = new Animation("player hit", 2);
    m_animations[DEAD] = new Animation("player dead", 4, false);
    m_animations[DOOR_IN] = new Animation("player door in", 8, false);
    m_animations[DOOR_OUT] = new Animation("player door out", 8, false);

    m_curAnimation = IDLE;
    m_currentState = ON_GROUND;
    m_animations[m_curAnimation]->start();
    m_currentAttackState = ON_NORMAL;
}

void Player::draw()
{
    PlatformerObject::draw();
}

void Player::update()
{
    this->handleInput();
    PlatformerObject::update();
    DamageableObject::update();
    AttackableObject::update();
    this->updateAnimation();
}

void Player::updateAnimation()
{
    ANIMATION_ID newAnimation = m_curAnimation;

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
        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
            newAnimation = RUN;
        } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
            newAnimation = RUN;
        } else {
            newAnimation = IDLE;
        }
        break;
    case ON_FLY:
        if (this->getBody()->GetLinearVelocity().y == 0) {
            m_currentState = ON_GROUND;
            break;
        }

        if (this->getBody()->GetLinearVelocity().y < 0) {
            newAnimation = JUMP;
        } else {
            newAnimation = FALL;
        }
        break;
    }

    switch (m_currentAttackState) {
    case ON_NORMAL: break;
    case ON_HIT: newAnimation = HIT; break;
    case ON_ATTACK: newAnimation = ATTACK; break;
    case ON_DIE: newAnimation = DEAD; break;
    }

    if (newAnimation != m_curAnimation) {
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
}

void Player::handleInput()
{
    if (m_currentState == ON_GROUND) {
        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
            float impulse = -m_pBody->GetMass() * 6;
            m_pBody->ApplyLinearImpulse(b2Vec2(impulse, 0), m_pBody->GetWorldCenter(), 1);
            m_direction = DIRECTION_LEFT;
            m_bTurnRight = false;
            m_bFlipped = true;
        } else if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
            float impulse = m_pBody->GetMass() * 6;
            m_pBody->ApplyLinearImpulse(b2Vec2(impulse, 0), m_pBody->GetWorldCenter(), 1);
            m_direction = DIRECTION_RIGHT;
            m_bFlipped = false;
            m_bTurnRight = true;
        }

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
            float impulse = -m_pBody->GetMass() * 300 * Box2D::PPM;
            m_pBody->ApplyLinearImpulse(b2Vec2(0, impulse), m_pBody->GetWorldCenter(), 1);
        }
    }

    if (m_currentAttackState == ON_NORMAL) {
        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
            this->attack();
        }
    }
};
