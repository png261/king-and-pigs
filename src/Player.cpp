#include "Player.hpp"

#include <memory>
#include "Animation.hpp"
#include "AttackableObject.hpp"
#include "Camera.hpp"
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "InputHandler.hpp"
#include "PhysicWorld.hpp"

Player::Player()
    : GameObject()
    , DamageableObject(3, 1000, 500)
    , AttackableObject(1, 30, 300)
    , m_bDoorIn(false)
    , m_bWantDoorIn(false)
{}

Player::~Player() {}


void Player::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    m_moveSpeed = 100;
    m_jumpHeight = 20.0f;

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_PLAYER;
    filter.maskBits = PhysicWorld::MASK_PLAYER;
    m_pFixture->SetFilterData(filter);

    this->createAttackSensor(getBody(), m_width, PhysicWorld::MASK_PLAYER_ATTACK_SENSOR);
    this->loadAnimation();
}

void Player::loadAnimation()
{
    m_animations[Animation::IDLE] =
        std::make_unique<Animation>(Animation("player idle", 78, 58, 11));
    m_animations[Animation::RUN] = std::make_unique<Animation>(Animation("player run", 78, 58, 8));
    m_animations[Animation::JUMP] =
        std::make_unique<Animation>(Animation("player jump", 78, 58, 1));
    m_animations[Animation::FALL] =
        std::make_unique<Animation>(Animation("player fall", 78, 58, 1));
    m_animations[Animation::GROUND] =
        std::make_unique<Animation>(Animation("player ground", 78, 58, 1));
    m_animations[Animation::ATTACK] =
        std::make_unique<Animation>(Animation("player attack", 78, 58, 3, false));
    m_animations[Animation::HIT] = std::make_unique<Animation>(Animation("player hit", 78, 58, 2));
    m_animations[Animation::DYING] =
        std::make_unique<Animation>(Animation("player dead", 78, 58, 4, false));
    m_animations[Animation::DOOR_IN] =
        std::make_unique<Animation>(Animation("player door in", 78, 58, 8, false));
    m_animations[Animation::DOOR_OUT] =
        std::make_unique<Animation>(Animation("player door out", 78, 58, 8, false));

    doorOutTimer.setTime(300);
    m_curAnimation = Animation::DOOR_OUT;
    m_animations[m_curAnimation]->start();
    doorOutTimer.start();
}

void Player::update()
{
    if (this->isDead()) {
        return;
    }

    this->handleInput();
    GameObject::update();
    DamageableObject::update();
    AttackableObject::update();
    this->updateAnimation();
}

void Player::handleInput()
{
    if (m_bDoorIn) {
        m_bWantDoorIn = true;
        return;
    }

    InputHandler* const input = InputHandler::Instance();

    if (this->isOnGround()) {
        if (input->isKeyDown(KEY_W)) {
            m_bWantDoorIn = true;
        } else {
            m_bWantDoorIn = false;
        }

        if (input->isKeyPressed(KEY_SPACE)) {
            this->jump();
        }
    }
    if (input->isKeyPressed(KEY_RIGHT)) {
        this->moveRight();
        m_bFlipped = false;
    }
    if (input->isKeyPressed(KEY_LEFT)) {
        this->moveLeft();
        m_bFlipped = true;
    }

    if (input->isKeyPressed(KEY_A)) {
        this->attack();
    }
};

void Player::updateAnimation()
{
    if (m_bDoorIn) {
        return;
    }

    Animation::AnimationID newAnimation = m_curAnimation;

    if (this->isOnGround()) {
        if (InputHandler::Instance()->isKeyPressed(KEY_LEFT)) {
            newAnimation = Animation::RUN;
        } else if (InputHandler::Instance()->isKeyPressed(KEY_RIGHT)) {
            newAnimation = Animation::RUN;
        } else {
            newAnimation = Animation::IDLE;
        }
    } else {
        if (this->getBody()->GetLinearVelocity().y < 0) {
            newAnimation = Animation::JUMP;
        } else {
            newAnimation = Animation::FALL;
        }
    }

    if (this->isInvulnerable()) {
        newAnimation = Animation::HIT;
    } else if (this->isAttack()) {
        newAnimation = Animation::ATTACK;
    } else if (this->isDying()) {
        newAnimation = Animation::DYING;
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
    m_curAnimation = Animation::DOOR_IN;
    m_animations[m_curAnimation]->start();
}

void Player::doorOut()
{
    m_curAnimation = Animation::DOOR_OUT;
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
