#include "Pig.hpp"
#include "DamageableObject.hpp"
#include "DebugDraw.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"
#include "PhysicWorld.hpp"

Pig::Pig()
    : Enemy()
    , DamageableObject(3, 300, 1000)
    , AttackableObject(1, 50, 300)
    , m_followPosition(0, 0)
    , m_originPosition(0, 0)
    , m_bSeeingPlayer(false)
    , m_bReachRight(false)
    , m_bCanAttackPlayer(false)
{}

void Pig::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Enemy::load(std::move(pParams));
    m_moveSpeed = 50;
    m_jumpHeight = 32.0f;
    m_originPosition = this->getPosition();
    this->createAttackSensor(getBody(), m_width, PhysicWorld::MASK_ENEMY_ATTACK_SENSOR);
    this->loadAnimation();

    m_currentAttackState = ON_NORMAL;
}

void Pig::loadAnimation()
{
    m_animations[Animation::IDLE] = std::make_unique<Animation>(Animation("pig idle", 34, 28, 11));
    m_animations[Animation::RUN] = std::make_unique<Animation>(Animation("pig run", 34, 28, 6));
    m_animations[Animation::JUMP] = std::make_unique<Animation>(Animation("pig jump", 34, 28, 1));
    m_animations[Animation::FALL] = std::make_unique<Animation>(Animation("pig fall", 34, 28, 1));
    m_animations[Animation::GROUND] = std::make_unique<Animation>(Animation("pig ground", 34, 28, 1));
    m_animations[Animation::ATTACK] = std::make_unique<Animation>(Animation("pig attack", 34, 28, 3, false));
    m_animations[Animation::HIT] = std::make_unique<Animation>(Animation("pig hit", 34, 28, 2));
    m_animations[Animation::DEAD] = std::make_unique<Animation>(Animation("pig dead", 34, 28, 4, false));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void Pig::update()
{
    /* this->handleMovement(); */
    Enemy::update();
    DamageableObject::update();
    AttackableObject::update();
    this->updateAnimation();


    DebugDraw* draw = new DebugDraw(Game::Instance()->getWindow());
    b2Vec2 start = m_pBody->GetPosition();
    b2Vec2 end = b2Vec2(start.x + 10, start.y);
    draw->DrawSegment(start, end, b2Color(1, 1, 1, 1));

    EnemyRayCastCallback callback;
    callback.setListener(this);
    PhysicWorld::Instance()->getWorld()->RayCast(&callback, start, end);
}

void Pig::updateAnimation()
{
    Animation::AnimationID newAnimation = m_curAnimation;
    if (this->isDead()) {
        m_bExist = false;
    } else if (this->isInvulnerable()) {
        m_currentAttackState = ON_HIT;
    } else if (this->isAttack()) {
        m_currentAttackState = ON_ATTACK;
    } else if (this->isDying()) {
        m_currentAttackState = ON_DYING;
    } else {
        m_currentAttackState = ON_NORMAL;
    }

    switch (m_currentState) {
    case ON_GROUND:
        newAnimation = Animation::IDLE;
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
    case ON_DYING:
        newAnimation = Animation::DEAD;
        break;
    }

    if (newAnimation != m_curAnimation) {
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
}

void Pig::setFollowPosition(b2Vec2 position)
{
    m_followPosition = position;
    m_originPosition = position;
}

void Pig::scanMode()
{
    m_moveSpeed = 50;
    b2Vec2 curPosition = this->getPosition();
    if (curPosition.x > m_originPosition.x + 200) {
        m_bReachRight = true;
    }

    if (curPosition.x < m_originPosition.x - 200) {
        m_bReachRight = false;
    }

    if (m_bReachRight == false) {
        this->moveRight();
    } else {
        this->moveLeft();
    }
};

void Pig::handleMovement()
{
    if (m_bSeeingPlayer == false) {
        this->scanMode();
    } else {
        this->followMode();
    }

    if (m_bCanAttackPlayer) {
        this->attack();
    }
}

void Pig::followMode()
{
    m_moveSpeed = 75;
    b2Vec2 curPosition = this->getPosition();
    if (m_followPosition.x > curPosition.x) {
        this->moveRight();
    } else if (m_followPosition.x < curPosition.x) {
        this->moveLeft();
    }
}

void Pig::setSeeingPlayer(bool isSeeing)
{
    m_bSeeingPlayer = isSeeing;
}

void Pig::setCanAttackPlayer(bool canAttackPlayer)
{
    m_bCanAttackPlayer = canAttackPlayer;
}
