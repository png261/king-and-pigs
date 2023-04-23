#pragma once

#include <box2d/box2d.h>

class ContactListener final : public b2ContactListener
{
public:
    void BeginContact(b2Contact* const contact) override;
    void EndContact(b2Contact* const contact) override;
    void PreSolve(b2Contact* const contact, const b2Manifold* oldManifold) override;
    void PostSolve(b2Contact* const contact, const b2ContactImpulse* impulse) override;

    void realTimeListener();

private:
    void AttackListener(b2Contact* const contact);
    void handleAttack(b2Fixture* const Attacker, b2Fixture* const Defender);
    void EnterDoorListener(b2Contact* const contact);

    void ItemBeginContact(b2Contact* const contact);
    void FootBeginContact(b2Contact* const contact);
    void FootEndContact(b2Contact* const contact);
    void OneWayPreSolve(b2Contact* const contact, const b2Manifold* oldManifold);
};
