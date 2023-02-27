#include "Box.hpp"
#include <iostream>
#include "Box2D.hpp"
#include "DamageableObject.hpp"

Box::Box()
    : Enemy()
    , DamageableObject(1, 200)
{}

void Box::load(const LoaderParams* pParams)
{
    Enemy::load(pParams);

    m_pBody->SetFixedRotation(false);
    m_animations[IDLE] = new Animation("box idle", 1);
    m_animations[HIT] = new Animation("box hit", 2);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void Box::update()
{
    Enemy::update();
    DamageableObject::update();
    this->updateAnimation();
}

void Box::updateAnimation()
{
    ANIMATION_ID newAnimation = m_curAnimation;

    if (this->isInvulnerable()) {
        newAnimation = HIT;
    } else if (this->isDead()) {
        m_bExist = false;
    } else {
        newAnimation = IDLE;
    }

    if (newAnimation != m_curAnimation) {
        m_animations[m_curAnimation]->stop();
        m_curAnimation = newAnimation;
        m_animations[m_curAnimation]->start();
    }
}

void Box::draw()
{
    Enemy::draw();
}

void Box::clean() {}
