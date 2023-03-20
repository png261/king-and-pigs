#pragma once

#include "AttackableObject.hpp"
#include "GameObject.hpp"

class Bomb final : public GameObject, public AttackableObject
{
public:
    Bomb();
    ~Bomb();

    void load(std::unique_ptr<LoaderParams> const& pParams);
    void update();
    void loadAnimation();
    void updateAnimaton();

    void turnOn();
    void explode();

    bool isOn() const;

private:
    bool m_bOn;
    Timer onTimer;
};
