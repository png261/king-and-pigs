#pragma once

#include "DamageableObject.hpp"
#include "Enemy.hpp"

class Box : public Enemy, public DamageableObject
{
public:
    Box();
    ~Box() {}

    void load(const LoaderParams* const pParams);

    void draw();
    void update();
    void clean();
    void updateAnimation();
};

