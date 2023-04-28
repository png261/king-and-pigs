#pragma once

#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "ObjectFactory.hpp"

class Box final : public GameObject, public DamageableObject
{
public:
    Box();

    void load(std::unique_ptr<LoaderParams> const& params) override;
    void update() override;
    void loadAnimation() override;
    void updateAnimation() override;

private:
    void randomBonus();
    void breakIntoPieces();

    enum AnimationID { NORMAL, HIT };
};

class BoxCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<Box>(); }
};
