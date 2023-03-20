#include "PigWithBomb.hpp"
#include "DamageableObject.hpp"

PigWithBomb::PigWithBomb()
    : Pig()
{}

PigWithBomb::~PigWithBomb() {}

void PigWithBomb::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Pig::load(std::move(pParams));
    this->loadAnimation();
}
void PigWithBomb::loadAnimation()
{
    Pig::loadAnimation();

    m_animations[Animation::IDLE] =
        std::make_unique<Animation>(Animation("pigWithBomb idle", 26, 26, 10));
    m_animations[Animation::RUN] =
        std::make_unique<Animation>(Animation("pigWithBomb run", 26, 26, 6));
    m_animations[Animation::THROWING] =
        std::make_unique<Animation>(Animation("pigWithBomb throwing", 26, 26, 5));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}

void PigWithBomb::update()
{
    Pig::update();
    this->updateAnimaton();
}

void PigWithBomb::updateAnimaton()
{
    Pig::updateAnimation();
}
