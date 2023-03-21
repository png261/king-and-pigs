#pragma once

#include "AttackableObject.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"

class Player final : public GameObject, public DamageableObject, public AttackableObject
{
public:
    Player();
    ~Player();
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void update() override;
    void updateAnimation() override;
    void loadAnimation() override;

    void doorIn();
    void doorOut();
    bool isWantDoorIn();
    bool isDoorIn();

private:
    void handleInput();
    Timer doorOutTimer;
    bool m_bDoorIn;
    bool m_bWantDoorIn;
};
