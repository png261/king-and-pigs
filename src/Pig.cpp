#include "Pig.h"
#include <iostream>
#include "Collision.h"
#include "Game.h"
#include "InputHandler.h"

Pig::Pig()
    : Enemy()
{}

void Pig::load(const LoaderParams* pParams)
{
    Enemy::load(pParams);
    m_currentState = ON_GROUND;
}

void Pig::update()
{
    std::cout << m_lives << std::endl;
    switch (m_currentState) {
    case ON_GROUND:
        /* setAnimation("pig idle"); */
        /* if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) { */
        /*     setAnimation("pig attack"); */
        /*     if (!Game::Instance()->getPlayer()->isInvulnerable() && */
        /*         checkCollision(this, Game::Instance()->getPlayer())) { */
        /*         Game::Instance()->getPlayer()->setCurrentState(ON_HIT); */
        /*         Game::Instance()->getPlayer()->setLives( */
        /*             (Game::Instance()->getPlayer()->getLives() - 1)); */
        /*     } */
        /* } else { */
        setAnimation("pig idle");
        /* } */
        break;
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
    case ON_ATTACK: break;
    case ON_DIE:
        if (m_aniCounter >= m_numFrames * 10) {
            m_aniCounter = 0;
            m_bDead = true;
            break;
        }
        setAnimation("pig dead");
        break;

    case ON_HIT:
        if (m_aniCounter >= m_numFrames * 10) {
            m_aniCounter = 0;
            m_currentState = ON_GROUND;
            m_bInvulnerable = false;
            m_velocity.setX(0);
            break;
        }
        if (m_lives <= 0) {
            m_currentState = ON_DIE;
            break;
        }

        m_bInvulnerable = true;
        setAnimation("pig hit");
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

void Pig::onHit()
{
    if (m_bInvulnerable && m_currentState != ON_DIE) {
        return;
    }

    m_lives -= 1;
    m_currentState = ON_HIT;
}
