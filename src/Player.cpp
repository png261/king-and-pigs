#include "Animation.hpp"
#include "AttackableObject.hpp"
#include "Box2D.hpp"
#include "Camera.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "SoundManager.hpp"

Player::Player()
    : GameObject()
    , DamageableObject(3, 300)
    , AttackableObject(1, 50, 300)
{}

void Player::load(const LoaderParams* const pParams)
{
    GameObject::load(pParams);

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
    m_animations[m_curAnimation]->start();
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
    InputHandler* const input = InputHandler::Instance();

    if (m_currentState == ON_GROUND) {
        if (input->isKeyPressed(KEY_SPACE)) {
            this->jump();
        }
        if (input->isKeyPressed(KEY_RIGHT)) {
            this->moveRight();
        }
        if (input->isKeyPressed(KEY_LEFT)) {
            this->moveLeft();
        }
    }

    if (m_currentAttackState == ON_NORMAL) {
        if (input->isKeyPressed(KEY_A)) {
            this->attack();
        }
    }
};

void Player::moveRight()
{
    float maxSpeed = Box2D::pixelToMeter(100); // Maximum speed in meters per second
    b2Body* playerBody = m_pBody;
    // Assume we have a b2Body* playerBody that represents the player's body
    float mass = playerBody->GetMass();
    float groundFriction = 2; // Ground friction coefficient
    bool isGrounded = true; // Flag indicating if player is grounded

    b2Vec2 currentVelocity = playerBody->GetLinearVelocity();
    float currentSpeed = currentVelocity.x;

    // Calculate the impulse required to reach the maximum speed
    float speedDifference = maxSpeed - currentSpeed;
    float impulse = mass * speedDifference;

    // Apply the impulse to the player's body to move it to the right
    b2Vec2 impulseDirection(1.0f, 0.0f); // Move player to the right
    impulseDirection.Normalize();
    playerBody->ApplyLinearImpulse(impulse * impulseDirection, playerBody->GetWorldCenter(), true);

    /* // Set the player's linear velocity to the maximum speed if it exceeds it */
    /* b2Vec2 newVelocity = playerBody->GetLinearVelocity(); */
    /* newVelocity.x = std::min(newVelocity.x, maxSpeed); */
    /* playerBody->SetLinearVelocity(newVelocity); */

    m_bTurnRight = true;
    m_bFlipped = false;
}

void Player::moveLeft()
{
    float maxSpeed = -Box2D::pixelToMeter(100); // Maximum speed in meters per second
    b2Body* playerBody = m_pBody;
    // Assume we have a b2Body* playerBody that represents the player's body
    float mass = playerBody->GetMass();
    float groundFriction = 2; // Ground friction coefficient
    bool isGrounded = true; // Flag indicating if player is grounded

    b2Vec2 currentVelocity = playerBody->GetLinearVelocity();
    float currentSpeed = currentVelocity.x;

    // Calculate the impulse required to reach the maximum speed
    float speedDifference = maxSpeed - currentSpeed;
    float impulse = mass * speedDifference;

    // Apply the impulse to the player's body to move it to the right
    b2Vec2 impulseDirection(1.0f, 0.0f); // Move player to the right
    impulseDirection.Normalize();
    playerBody->ApplyLinearImpulse(impulse * impulseDirection, playerBody->GetWorldCenter(), true);

    m_bTurnRight = false;
    m_bFlipped = true;
}

void Player::jump()
{
    float mass = m_pBody->GetMass();
    float gravity = 9.8f;
    float jumpHeight = 0.5; // Jump height in meters

    float timeToJumpPeak = sqrt(2 * jumpHeight / gravity);
    b2Vec2 impulse = -b2Vec2(0, mass * jumpHeight / timeToJumpPeak);
    m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
}
