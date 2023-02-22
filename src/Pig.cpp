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
    case ON_FLY: newAnimation = JUMP; break;
    case ON_FALL: newAnimation = FALL; break;
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
