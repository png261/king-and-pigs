#include "Pig.hpp"
#include "Collision.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

Pig::Pig()
    : Enemy()
{}

void Pig::load(const LoaderParams* pParams)
{
    Enemy::load(pParams);
    m_currentState = ON_GROUND;
    m_currentAttackState = ON_NORMAL;
}

void Pig::update()
{
    switch (m_currentState) {
    case ON_GROUND: setAnimation("pig idle"); break;
    case ON_FLY:
        if (m_velocity.getY() > 0) {
            setAnimation("pig fall");
            m_currentState = ON_FALL;
        } else if (m_velocity.getY() < 0) {
            setAnimation("pig jump");
        }
        break;
    case ON_FALL:
        if (m_velocity.getY() == 0) {
            setAnimation("pig ground");
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
        if (m_startState == 0) {
            m_startState = SDL_GetTicks();
        }

        if (SDL_GetTicks() - m_startState >= 300) {
            m_currentAttackState = ON_NORMAL;
            m_bInvulnerable = false;
            m_velocity.setX(0);
            break;
        }

        m_bInvulnerable = true;
        setAnimation("pig hit");

        break;
    case ON_ATTACK:
        if (m_startState == 0) {
            m_startState = SDL_GetTicks();
        }

        if (SDL_GetTicks() - m_startState >= 300) {
            m_currentAttackState = ON_NORMAL;
            m_startState = 0;
            m_bAttack = false;
            break;
        }
        m_bAttack = true;
        setAnimation("pig attack");
        break;
    case ON_DIE:
        if (m_startState == 0) {
            m_startState = SDL_GetTicks();
        }

        if (SDL_GetTicks() - m_startState >= 300) {
            m_bDead = true;
            break;
        };

        setAnimation("pig die");
        break;
    }
    m_aniCounter++;

    Enemy::update();
}

void Pig::draw()
{
    Enemy::draw();
}

void Pig::clean() {}
