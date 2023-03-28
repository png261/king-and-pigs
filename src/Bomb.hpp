#pragma once

#include "AttackerObject.hpp"
#include "GameObject.hpp"

class Bomb final : public GameObject, public AttackerObject
{
public:
    Bomb();
    ~Bomb();

    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void update() override;
    void loadAnimation() override;

    void updateAnimaton();

    void turnOn();
    void explode();

    bool isOn() const;

private:
    enum animations { OFF, ON, EXPLODE };
    bool m_bOn;
    Timer onTimer;
};
