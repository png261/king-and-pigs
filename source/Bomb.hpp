#pragma once

#include "AttackerObject.hpp"
#include "GameObject.hpp"
#include "ObjectFactory.hpp"

class Bomb final : public GameObject, public AttackerObject
{
public:
    Bomb();

    void load(const LoaderParams& params) override;
    void update() override;
    void loadAnimation() override;

    void updateAnimaton();

    void turnOn();
    void explode();

    bool isOn() const;

private:
    enum AnimationID { OFF, ON, EXPLODE };
    bool is_on_;
    Timer on_timer_;
};

class BombCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<Bomb>(); }
};
