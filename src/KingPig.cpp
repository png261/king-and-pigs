#include "KingPig.hpp"

KingPig::KingPig()
    : Pig()
{}

void KingPig::loadAnimation()
{
    m_animations[Animation::IDLE] =
        std::make_unique<Animation>(Animation("kingPig idle", 38, 28, 11));
    m_animations[Animation::RUN] = std::make_unique<Animation>(Animation("kingPig run", 38, 28, 6));
    m_animations[Animation::JUMP] =
        std::make_unique<Animation>(Animation("kingPig jump", 38, 28, 1));
    m_animations[Animation::FALL] =
        std::make_unique<Animation>(Animation("kingPig fall", 38, 28, 1));
    m_animations[Animation::GROUND] =
        std::make_unique<Animation>(Animation("kingPig ground", 38, 28, 1));
    m_animations[Animation::ATTACK] =
        std::make_unique<Animation>(Animation("kingPig attack", 38, 28, 3, false));
    m_animations[Animation::HIT] = std::make_unique<Animation>(Animation("kingPig hit", 38, 28, 2));
    m_animations[Animation::DYING] =
        std::make_unique<Animation>(Animation("kingPig dead", 38, 28, 4, false));

    m_curAnimation = Animation::IDLE;
    m_animations[m_curAnimation]->start();
}
