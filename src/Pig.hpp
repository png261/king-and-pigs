#pragma once

#include "AttackableObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "Log.hpp"

class Pig : public GameObject, public DamageableObject, public AttackableObject
{
public:
    Pig();
    virtual void load(std::unique_ptr<LoaderParams> const& pParams) override;
    virtual void loadAnimation() override;
    virtual void update() override;
    virtual void updateAnimation() override;
};
