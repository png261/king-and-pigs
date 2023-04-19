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
    , AttackerObject(1, 20, 500)
{}

void Pig::load(std::unique_ptr<LoaderParams> const& pParams)
{
    GameObject::load(std::move(pParams));
    createBody(pParams->x(), pParams->y(), m_width, m_height);
    setFilterData(PhysicWorld::CAT_PIG, PhysicWorld::MASK_PIG);
    m_pFixture->SetDensity(50);

    createCircleSensor(
        -b2Vec2((m_width * 0.5 + m_attackRange) * 0.5, 0),
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    createCircleSensor(
        b2Vec2((m_width * 0.5 + m_attackRange) * 0.5, 0),
        m_attackRange,
        PhysicWorld::CAT_ATTACK_SENSOR,
        PhysicWorld::MASK_PIG_ATTACK_SENSOR);

    m_moveSpeed = 40;
    m_jumpHeight = 32.0f;
    m_direction = LEFT;

    loadAnimation();
}

void Pig::loadAnimation()
{
    m_animations[IDLE] = std::make_unique<Animation>("pig_idle", 34, 28, 11);
    m_animations[RUN] = std::make_unique<Animation>("pig_run", 34, 28, 6);
    m_animations[JUMP] = std::make_unique<Animation>("pig_jump", 34, 28, 1);
    m_animations[FALL] = std::make_unique<Animation>("pig_fall", 34, 28, 1);
    m_animations[GROUND] = std::make_unique<Animation>("pig_ground", 34, 28, 1);
    m_animations[ATTACK] = std::make_unique<Animation>("pig_attack", 34, 28, 5);
    m_animations[HIT] = std::make_unique<Animation>("pig_hit", 34, 28, 2);
    m_animations[DYING] = std::make_unique<Animation>("pig_dead", 34, 28, 4, false);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void Pig::update()
{
    if (isDead()) {
        disappear();
        return;
    }

    GameObject::update();
    m_raycast.clear();
    float nray = 50;
    for (int i = 0; i < nray; ++i) {
        b2Vec2 start = getPosition() + m_direction * (b2Vec2(m_width / 2.0f, 0)) +
                       b2Vec2(0, -m_height / 2.0f + i * m_height / nray);
        b2Vec2 end = start + m_direction * b2Vec2(m_visionRange, 0);
        m_raycast.push_back({start, end});
    }

    VisionObject::update();
    VisionObject::update();
    handleMovement();
    m_bFlipped = m_direction == RIGHT;

    DamageableObject::update();
    AttackerObject::update();
    updateAnimation();
    handleSound();
}

void Pig::handleSound()
{
    if (isDying()) {
        SoundManager::Instance().playSFX("pig_dying");
    }

    if (isAttack()) {
        SoundManager::Instance().playSFX("pig_attack");
    }
}

void Pig::handleMovement()
{
    if (isDying()) {
        return;
    }

    if (m_direction == RIGHT) {
        moveRight();
    } else {
        moveLeft();
    }

    if (isSeeing(PhysicWorld::CAT_PLAYER)) {
        seeingPlayer();
    }
    if (isSeeing(PhysicWorld::CAT_WALL)) {
        seeingWall();
    }
    if (isSeeing(PhysicWorld::CAT_BOX)) {
        seeingBox();
    }
    if (isSeeing(PhysicWorld::CAT_PIG)) {
        seeingPig();
    }
}

void Pig::seeingPlayer()
{
    if (m_visionNearestDistance >= m_attackRange) {
        return;
    }
    if (canAttack()) {
        attack();
    }
}

void Pig::changeDirection()
{
    if (m_direction == RIGHT) {
        setMoveRight(false);
        setMoveLeft(true);
        m_direction = LEFT;
    } else {
        setMoveLeft(false);
        setMoveRight(true);
        m_direction = RIGHT;
    }
}
void Pig::seeingWall()
{
    if (m_visionNearestDistance >= 1) {
        return;
    }
    changeDirection();
}

void Pig::seeingBox()
{
    if (m_visionNearestDistance >= 10) {
        return;
    }
    if (isDisableJump()) {
        changeDirection();
    } else {
        jump();
    }
}

void Pig::seeingPig()
{
    if (m_visionNearestDistance >= 10) {
        return;
    }

    changeDirection();
}

void Pig::updateAnimation()
{
    int newAnimation = m_curAnimation;

    if (isOnGround()) {
        if (m_curAnimation == FALL) {
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
