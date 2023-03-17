#pragma once

#include "AttackableObject.hpp"
#include "Enemy.hpp"
#include "Log.hpp"

class Pig : public Enemy, public DamageableObject, public AttackableObject
{
public:
    Pig();
    void load(std::unique_ptr<LoaderParams> const& pParams);
    void loadAnimation();
    void update();
    void updateAnimation();
    void handleMovement();

    void setSeeingPlayer(bool isSeeing);
    void setCanAttackPlayer(bool isPlayerInAttackRange);
    void setFollowPosition(b2Vec2 position);
    void scanMode();
    void followMode();

    bool isSeeingPlayer() { return m_bSeeingPlayer; }

private:
    bool m_bReachRight;
    b2Vec2 m_originPosition;
    b2Vec2 m_followPosition;
    bool m_bSeeingPlayer;
    bool m_bCanAttackPlayer;
};

class EnemyRayCastCallback : public b2RayCastCallback
{
public:
    EnemyRayCastCallback()
        : m_listener(nullptr)
    {}
    void setListener(Pig* listener) { m_listener = listener; }
    float ReportFixture(
        b2Fixture* fixture,
        const b2Vec2& point,
        const b2Vec2& normal,
        float fraction) override
    {
        if (fixture->GetFilterData().categoryBits == PhysicWorld::CAT_PLAYER) {
            Log::log("seeing player");
            m_listener->setSeeingPlayer(true);
        }
        if (fixture->GetFilterData().categoryBits == PhysicWorld::CAT_ENEMY) {
            m_listener->setSeeingPlayer(false);
        }
        return -1;
    }

private:
    Pig* m_listener;
};
