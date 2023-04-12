#pragma once

#include "DamageableObject.hpp"
#include "GameObject.hpp"

class Box final : public GameObject, public DamageableObject
{
public:
    Box();

    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void update() override;
    void loadAnimation() override;
    void updateAnimation() override;

private:
    void randomBonus();
    void breakIntoPieces();

    enum animation { NORMAL, HIT };
};
