#include "Animation.hpp"
#include "AttackableObject.hpp"
#include "Box2D.hpp"
#include "Camera.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "GameObject.hpp"
#include "SoundManager.hpp"

Player::Player()
    : GameObject()
    , DamageableObject(3, 300)
    , AttackableObject(1, 50, 300)
{}

void Player::load(const LoaderParams* const pParams)
{
    m_moveSpeed = 6 * Box2D::PPM;
    m_jumpSpeed = -6 * Box2D::PPM;

    GameObject::load(pParams);

    b2Filter filter;
    filter.categoryBits = Box2D::CAT_PLAYER;
    filter.maskBits = Box2D::MASK_PLAYER;
    m_pFixture->SetFilterData(filter);

    this->createAttackSensor(getBody(), m_width, Box2D::MASK_PLAYER_ATTACK_SENSOR);

    m_animations[Animation::IDLE] = new Animation("player idle", 11);
    m_animations[Animation::RUN] = new Animation("player run", 8);
    m_animations[Animation::JUMP] = new Animation("player jump", 1);
    m_animations[Animation::FALL] = new Animation("player fall", 1);
    m_animations[Animation::GROUND] = new Animation("player ground", 1);
    m_animations[Animation::ATTACK] = new Animation("player attack", 3, false);
    m_animations[Animation::HIT] = new Animation("player hit", 2);
    m_animations[Animation::DEAD] = new Animation("player dead", 4, false);
    m_animations[Animation::DOOR_IN] = new Animation("player door in", 8, false);
    m_animations[Animation::DOOR_OUT] = new Animation("player door out", 8, false);

    m_curAnimation = Animation::IDLE;
    m_currentState = ON_GROUND;
    m_animations[m_curAnimation]->start();
    m_currentAttackState = ON_NORMAL;
}

void Player::draw()
{
    GameObject::draw();
}

void Player::update()
{
    this->handleInput();
    GameObject::update();
    DamageableObject::update();
    AttackableObject::update();
    this->updateAnimation();
}

void Player::updateAnimation()
{
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
        if (InputHandler::Instance()->isKeyDown(KEY_LEFT)) {
            newAnimation = Animation::RUN;
        } else if (InputHandler::Instance()->isKeyDown(KEY_RIGHT)) {
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
    case ON_NORMAL: break;
    case ON_HIT: newAnimation = Animation::HIT; break;
    case ON_ATTACK: newAnimation = Animation::ATTACK; break;
    case ON_DIE: newAnimation = Animation::DEAD; break;
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
        if (InputHandler::Instance()->isKeyDown(KEY_LEFT)) {
            float impulse = -m_pBody->GetMass() * 6;
            m_pBody->ApplyLinearImpulse(b2Vec2(impulse, 0), m_pBody->GetWorldCenter(), 1);
            m_bTurnRight = false;
            m_bFlipped = true;
        } else if (InputHandler::Instance()->isKeyDown(KEY_RIGHT)) {
            float impulse = m_pBody->GetMass() * 6;
            m_pBody->ApplyLinearImpulse(b2Vec2(impulse, 0), m_pBody->GetWorldCenter(), 1);
            m_bFlipped = false;
            m_bTurnRight = true;
        }

        if (InputHandler::Instance()->isKeyDown(KEY_SPACE)) {
            float impulse = -m_pBody->GetMass() * 100 * Box2D::PPM;
            m_pBody->ApplyLinearImpulse(b2Vec2(0, impulse), m_pBody->GetWorldCenter(), 1);
        }
    }

    if (m_currentAttackState == ON_NORMAL) {
        if (InputHandler::Instance()->isKeyDown(KEY_A)) {
            this->attack();
        }
    }
};
