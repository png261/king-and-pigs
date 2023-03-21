#include "Box.hpp"
#include "DamageableObject.hpp"
#include "PhysicWorld.hpp"

Box::Box()
    : Enemy()
    , DamageableObject(1, 200, 300)
{}

void Box::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Enemy::load(std::move(pParams));

    m_pBody->SetFixedRotation(false);
    m_pFixture->SetDensity(0.5);
    m_pFixture->SetFriction(0.3);
    m_animations[Animation::IDLE] = std::make_unique<Animation>(Animation("box idle", 22, 16, 1));
    m_animations[Animation::HIT] = std::make_unique<Animation>(Animation("box hit", 22, 16, 2));

    m_curAnimation = Animation::IDLE;
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
    Animation::AnimationID newAnimation = m_curAnimation;

    if (this->isInvulnerable()) {
        newAnimation = Animation::HIT;
    } else if (this->isDead()) {
        this->disappear();
    } else {
        newAnimation = Animation::IDLE;
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
