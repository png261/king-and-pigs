#pragma once

#include "AttackerObject.hpp"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"

class Bomb final : public GameObject, public AttackerObject
{
public:
    Bomb();

    void load(std::unique_ptr<LoaderParams> const& params) override;
    void update() override;
    void loadAnimation() override;

    void updateAnimaton();

    void turnOn();
    void explode();

    bool isOn() const;

private:
    enum animations { OFF, ON, EXPLODE };
    bool is_on_;
    Timer on_timer_;
};

class BombCreator : public BaseCreator
{
    std::unique_ptr<GameObject> create() const { return std::make_unique<Bomb>(); }
};
