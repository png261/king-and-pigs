#include "Pig.h"
#include "InputHandler.h"
#include <iostream>

Pig::Pig() : Enemy() {}

void Pig::load(const LoaderParams *pParams) { Enemy::load(pParams); }

void Pig::update() {
    if (m_currentState == PIG_ON_GROUND) {
        setAnimation("enemy_pig idle");
    } else if (m_currentState == PIG_ON_FLY) {
        if (m_velocity.getY() > 0) {
            setAnimation("enemy_pig fall");
        } else if (m_velocity.getY() < 0) {
            setAnimation("enemy_pig jump");
        } else if (m_velocity.getY() == 0) {
            setAnimation("enemy_pig ground");
            m_currentState = PIG_ON_GROUND;
        }
    }
    Enemy::update();
}

void Pig::draw() { Enemy::draw(); }

void Pig::clean() {}

void Pig::colision() {}
