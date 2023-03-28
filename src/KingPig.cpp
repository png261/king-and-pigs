#include "KingPig.hpp"

KingPig::KingPig()
    : Pig()
{}

void KingPig::loadAnimation()
{
    m_animations[IDLE] = new Animation("kingPig idle", 38, 28, 11);
    m_animations[RUN] = new Animation("kingPig run", 38, 28, 6);
    m_animations[JUMP] = new Animation("kingPig jump", 38, 28, 1);
    m_animations[FALL] = new Animation("kingPig fall", 38, 28, 1);
    m_animations[GROUND] = new Animation("kingPig ground", 38, 28, 1);
    m_animations[ATTACK] =
        new Animation("kingPig attack", 38, 28, 3, false);
    m_animations[HIT] = new Animation("kingPig hit", 38, 28, 2);
    m_animations[DYING] = new Animation("kingPig dead", 38, 28, 4, false);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}
