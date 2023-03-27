#include "Pig.hpp"
#include <iostream>
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"

Pig::Pig()
    : GameObject()
    , VisionObject(100)
    , DamageableObject(3, 300, 1000)
    , AttackerObject(1, 20, 300)
{}

void Pig::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    this->createBody(pParams->x(), pParams->y(), m_width, m_height);
    m_moveSpeed = 50;
    m_jumpHeight = 32.0f + m_height;
    m_direction = LEFT;

    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_PIG;
    filter.maskBits = PhysicWorld::MASK_PIG;
    m_pFixture->SetDensity(50);
    m_pFixture->SetFilterData(filter);

    PhysicWorld::Instance()->createCircleSensor(
        m_pBody,
        -b2Vec2((m_width * 0.5 + m_attackRange) * 0.5, 0),
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    PhysicWorld::Instance()->createCircleSensor(
        m_pBody,
        b2Vec2((m_width * 0.5 + m_attackRange) * 0.5, 0),
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    this->loadAnimation();
}

void Pig::loadAnimation()
{
    m_animations[Animation::IDLE] = std::make_unique<Animation>(Animation("pig idle", 34, 28, 11));
    m_animations[Animation::RUN] = std::make_unique<Animation>(Animation("pig run", 34, 28, 6));
    m_animations[Animation::JUMP] = std::make_unique<Animation>(Animation("pig jump", 34, 28, 1));
    m_animations[Animation::FALL] = std::make_unique<Animation>(Animation("pig fall", 34, 28, 1));
    m_animations[Animation::GROUND] =
        std::make_unique<Animation>(Animation("pig ground", 34, 28, 1));
    m_animations[Animation::ATTACK] =
        std::make_unique<Animation>(Animation("pig attack", 34, 28, 3, false));
    m_animations[Animation::HIT] = std::make_unique<Animation>(Animation("pig hit", 34, 28, 2));
    m_animations[Animation::DYING] =
        std::make_unique<Animation>(Animation("pig dead", 34, 28, 4, false));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void Pig::update()
{
    if (this->isDead()) {
        this->disappear();
        return;
    }

    GameObject::update();
    b2Vec2 start = this->getPosition() + m_direction * b2Vec2(m_width / 2.0f, 0);
    b2Vec2 end = start + m_direction * b2Vec2(m_orignRange, 0);
    VisionObject::update(start, end);
    /* this->handleMovement(); */
    m_bFlipped = m_direction == RIGHT;

    DamageableObject::update();
    AttackerObject::update();
    this->updateAnimation();
}

void Pig::handleMovement()
{
    if (this->isDying()) {
        return;
    }

    if (m_direction == RIGHT) {
        this->moveRight();
    } else {
        this->moveLeft();
    }

    switch (m_seeingCategory) {
    case PhysicWorld::CAT_WALL:
        this->seeingWall();
        break;
    case PhysicWorld::CAT_BOX:
        this->seeingBox();
        break;
    case PhysicWorld::CAT_PLAYER:
        this->seeingPlayer();
        break;
    case PhysicWorld::CAT_PIG:
        this->seeingPig();
        break;
    default:
        break;
    }
}

void Pig::seeingPlayer()
{
    if (m_nearestDistance >= 10) {
        return;
    }
    this->attack();
}

void Pig::seeingWall()
{
    if (m_nearestDistance >= 10) {
        this->setMoveRight(true);
        this->setMoveLeft(true);
        return;
    }

    if (m_direction == RIGHT) {
        this->setMoveRight(false);
        m_direction = LEFT;
    } else {
        this->setMoveLeft(false);
        m_direction = RIGHT;
    }
}

void Pig::seeingBox()
{
    if (m_nearestDistance >= 10) {
        return;
    }
    this->jump();
    if (m_direction == RIGHT) {
        this->moveRight();
    } else {
        this->moveLeft();
    }
}

void Pig::seeingPig()
{
    if (m_nearestDistance >= 10) {
        return;
    }
    this->jump();
    if (m_direction == RIGHT) {
        this->moveRight();
    } else {
        this->moveLeft();
    }
}

void Pig::updateAnimation()
{
    Animation::AnimationID newAnimation = m_curAnimation;

    if (this->isOnGround()) {
        newAnimation = Animation::IDLE;
    } else {
        if (this->getBody()->GetLinearVelocity().y < 0) {
            newAnimation = Animation::JUMP;
        } else {
            newAnimation = Animation::FALL;
        }
    }

    if (this->isRunning()) {
        newAnimation = Animation::RUN;
    }

    if (this->isDying()) {
        newAnimation = Animation::DYING;
    } else if (this->isInvulnerable()) {
        newAnimation = Animation::HIT;
    } else if (this->isAttack()) {
        newAnimation = Animation::ATTACK;
    }

    if (newAnimation != m_curAnimation) {
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
}

void Pig::draw()
{
    GameObject::draw();
    VisionObject::debugDraw();
}
