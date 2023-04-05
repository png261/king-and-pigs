#include "Pig.hpp"
#include <iostream>
#include "DamageableObject.hpp"
#include "Game.hpp"
#include "PhysicWorld.hpp"
#include "SoundManager.hpp"

Pig::Pig()
    : GameObject()
    , VisionObject(100)
    , DamageableObject(3, 300, 500)
    , AttackerObject(1, 20, 300)
{}

void Pig::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    this->createBody(pParams->x(), pParams->y(), m_width, m_height);
    this->setFilterData(PhysicWorld::CAT_PIG, PhysicWorld::MASK_PIG);
    m_pFixture->SetDensity(50);

    this->createCircleSensor(
        -b2Vec2((m_width * 0.5 + m_attackRange) * 0.5, 0),
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    this->createCircleSensor(
        b2Vec2((m_width * 0.5 + m_attackRange) * 0.5, 0),
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    m_moveSpeed = 40;
    m_jumpHeight = 32.0f;
    m_direction = LEFT;

    this->loadAnimation();
}

void Pig::loadAnimation()
{
    m_animations[IDLE] = std::make_unique<Animation>("pig idle", 34, 28, 11);
    m_animations[RUN] = std::make_unique<Animation>("pig run", 34, 28, 6);
    m_animations[JUMP] = std::make_unique<Animation>("pig jump", 34, 28, 1);
    m_animations[FALL] = std::make_unique<Animation>("pig fall", 34, 28, 1);
    m_animations[GROUND] = std::make_unique<Animation>("pig ground", 34, 28, 1);
    m_animations[ATTACK] = std::make_unique<Animation>("pig attack", 34, 28, 3, false);
    m_animations[HIT] = std::make_unique<Animation>("pig hit", 34, 28, 2);
    m_animations[DYING] = std::make_unique<Animation>("pig dead", 34, 28, 4, false);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void Pig::update()
{
    if (this->isDead()) {
        this->disappear();
        return;
    }

    GameObject::update();
    m_raycast.clear();
    float nray = 50;
    for (int i = 0; i < nray; ++i) {
        b2Vec2 start = this->getPosition() + m_direction * (b2Vec2(m_width / 2.0f, 0)) +
                       b2Vec2(0, -m_height / 2.0f + i * m_height / nray);
        b2Vec2 end = start + m_direction * b2Vec2(m_visionRange, 0);
        m_raycast.push_back({start, end});
    }

    VisionObject::update();
    VisionObject::update();
    this->handleMovement();
    m_bFlipped = m_direction == RIGHT;

    DamageableObject::update();
    AttackerObject::update();
    this->updateAnimation();
    this->handleSound();
}

void Pig::handleSound()
{
    if (this->isDying()) {
        SoundManager::Instance()->playSFX("pig dying");
    }

    if (this->isAttack()) {
        SoundManager::Instance()->playSFX("pig attack");
    }
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

    if (m_seeingCategory & PhysicWorld::CAT_PLAYER) {
        this->seeingPlayer();
    }
    if (m_seeingCategory & PhysicWorld::CAT_WALL) {
        this->seeingWall();
    }
    if (m_seeingCategory & PhysicWorld::CAT_BOX) {
        this->seeingBox();
    }
    if (m_seeingCategory & PhysicWorld::CAT_PIG) {
        this->seeingPig();
    }
}

void Pig::seeingPlayer()
{
    if (m_visionNearestDistance >= m_attackRange) {
        return;
    }
    if (this->canAttack()) {
        this->attack();
    }
}

void Pig::changeDirection()
{
    if (m_direction == RIGHT) {
        this->setMoveRight(false);
        this->setMoveLeft(true);
        m_direction = LEFT;
    } else {
        this->setMoveLeft(false);
        this->setMoveRight(true);
        m_direction = RIGHT;
    }
}
void Pig::seeingWall()
{
    if (m_visionNearestDistance >= 1) {
        return;
    }
    this->changeDirection();
}

void Pig::seeingBox()
{
    if (m_visionNearestDistance >= 10) {
        return;
    }
    if (this->isDisableJump()) {
        this->changeDirection();
    } else {
        this->jump();
    }
}

void Pig::seeingPig()
{
    if (m_visionNearestDistance >= 10) {
        return;
    }

    this->changeDirection();
}

void Pig::updateAnimation()
{
    int newAnimation = m_curAnimation;

    if (this->isOnGround()) {
        newAnimation = IDLE;
        if (this->isRunning()) {
            newAnimation = RUN;
        }
    } else {
        if (this->getBody()->GetLinearVelocity().y < 0) {
            newAnimation = JUMP;
        } else {
            newAnimation = FALL;
        }
    }

    if (this->isDying()) {
        newAnimation = DYING;
    } else if (this->isInvulnerable()) {
        newAnimation = HIT;
    } else if (this->isAttack()) {
        newAnimation = ATTACK;
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
