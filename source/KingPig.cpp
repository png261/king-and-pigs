#include "KingPig.hpp"

KingPig::KingPig()
    : Pig()
{}

void KingPig::loadAnimation()
{
    animations_[IDLE] = std::make_unique<Animation>("kingPig_idle", 38, 28, 11);
    animations_[RUN] = std::make_unique<Animation>("kingPig_run", 38, 28, 6);
    animations_[JUMP] = std::make_unique<Animation>("kingPig_jump", 38, 28, 1);
    animations_[FALL] = std::make_unique<Animation>("kingPig_fall", 38, 28, 1);
    animations_[GROUND] = std::make_unique<Animation>("kingPig_ground", 38, 28, 1);
    animations_[ATTACK] = std::make_unique<Animation>("kingPig_attack", 38, 28, 3, false);
    animations_[HIT] = std::make_unique<Animation>("kingPig_hit", 38, 28, 2);
    animations_[DYING] = std::make_unique<Animation>("kingPig_dead", 38, 28, 4, false);

    current_animation_ = IDLE;
    animations_[current_animation_]->start();
}
