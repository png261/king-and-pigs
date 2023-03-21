#pragma once

#include "DamageableObject.hpp"
#include "GameObject.hpp"

class Box : public GameObject, public DamageableObject
{
public:
    Box();
    ~Box() {}

    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void update() override;
    void loadAnimation() override;
    void updateAnimation() override;

    void breakIntoPieces();
};
