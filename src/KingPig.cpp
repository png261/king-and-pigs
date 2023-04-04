#include "KingPig.hpp"

KingPig::KingPig()
    : Pig()
{}

void KingPig::loadAnimation()
{
    m_animations[IDLE] = std::make_unique<Animation>("kingPig idle", 38, 28, 11);
    m_animations[RUN] = std::make_unique<Animation>("kingPig run", 38, 28, 6);
    m_animations[JUMP] = std::make_unique<Animation>("kingPig jump", 38, 28, 1);
    m_animations[FALL] = std::make_unique<Animation>("kingPig fall", 38, 28, 1);
    m_animations[GROUND] = std::make_unique<Animation>("kingPig ground", 38, 28, 1);
    m_animations[ATTACK] = std::make_unique<Animation>("kingPig attack", 38, 28, 3, false);
    m_animations[HIT] = std::make_unique<Animation>("kingPig hit", 38, 28, 2);
    m_animations[DYING] = std::make_unique<Animation>("kingPig dead", 38, 28, 4, false);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}
