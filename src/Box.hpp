#pragma once

#include "DamageableObject.hpp"
#include "Enemy.hpp"

class Box : public Enemy, public DamageableObject
{
public:
    Box();
    ~Box() {}

    void load(std::unique_ptr<LoaderParams> const& pParams) override;

    void draw() override;
    void update() override;
    void updateAnimation() override;
};
