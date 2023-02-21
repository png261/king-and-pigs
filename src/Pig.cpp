#include "Pig.hpp"
#include "Box2D.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

Pig::Pig()
    : Enemy()
{}

void Pig::load(const LoaderParams* pParams)
{
    Enemy::load(pParams);

    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;
    dynamicBox.SetAsBox(m_width / 2.0f, m_height / 2.0f);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.filter.categoryBits = Box2D::ENEMY;
    fixtureDef.filter.maskBits = Box2D::WALL | Box2D::PLAYER | Box2D::PLAYER_FOOT | Box2D::ENEMY;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    m_animations[IDLE] = new Animation("pig idle", 11);
    m_animations[RUN] = new Animation("pig run", 6);
    m_animations[JUMP] = new Animation("pig jump", 1);
    m_animations[FALL] = new Animation("pig fall", 1);
    m_animations[GROUND] = new Animation("pig ground", 1);
    m_animations[ATTACK] = new Animation("pig attack", 3);
    m_animations[HIT] = new Animation("pig hit", 2);
    m_animations[DEAD] = new Animation("pig dead", 4, false);

    m_currentState = ON_FLY;
    m_curAnimation = FALL;
    m_currentAttackState = ON_NORMAL;
}

void Pig::update()
{
    ANIMATION_ID newAnimation;
    switch (m_currentState) {
    case ON_GROUND: newAnimation = IDLE; break;
    case ON_FLY:
        if (m_velocity.y > 0) {
            newAnimation = FALL;
            m_currentState = ON_FALL;
        } else if (m_velocity.y < 0) {
            newAnimation = JUMP;
        }
        break;
    case ON_FALL:
        if (m_velocity.y == 0) {
            newAnimation = GROUND;
            m_currentState = ON_GROUND;
        }
        break;
    }

    switch (m_currentAttackState) {
    case ON_NORMAL:
        if (m_lives <= 0) {
            m_currentAttackState = ON_DIE;
            break;
        }

        if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_S)) {
            m_currentAttackState = ON_ATTACK;
            break;
        }

        break;
    case ON_HIT:
        timer.start();
        if (timer.delta() >= 300) {
            m_currentAttackState = ON_NORMAL;
            m_bInvulnerable = false;
            m_velocity.x = 0;
            timer.stop();
            break;
        }

        m_bInvulnerable = true;
        newAnimation = HIT;

        break;
    case ON_ATTACK:
        timer.start();

        if (timer.delta() >= 300) {
            m_currentAttackState = ON_NORMAL;
            timer.stop();
            m_bAttack = false;
            break;
        }
        m_bAttack = true;
        newAnimation = ATTACK;
        break;
    case ON_DIE:
        timer.start();

        if (timer.delta() >= 1000) {
            m_bDead = true;
            break;
        };

        newAnimation = DEAD;
        break;
    }

    if (newAnimation != m_curAnimation) {
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }

    Enemy::update();
}

void Pig::draw()
{
    Enemy::draw();
}

void Pig::clean() {}
