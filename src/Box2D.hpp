#ifndef BOX2D_HPP
#define BOX2D_HPP

#include <SDL2/SDL_gamecontroller.h>
#include <box2d/box2d.h>
#include <iostream>
#include "PlatformerObject.hpp"


namespace Box2D {
class ContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact)
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        if (fixtureA->IsSensor()) {
            PlatformerObject* obj =
                reinterpret_cast<PlatformerObject*>(fixtureA->GetBody()->GetUserData().pointer);
            obj->changeFootContact(+1);
        }

        b2Fixture* fixtureB = contact->GetFixtureB();
        if (fixtureB->IsSensor()) {
            PlatformerObject* obj =
                reinterpret_cast<PlatformerObject*>(fixtureB->GetBody()->GetUserData().pointer);
            obj->changeFootContact(+1);
        }
    }

    void EndContact(b2Contact* contact)
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        if (fixtureA->IsSensor()) {
            PlatformerObject* obj =
                reinterpret_cast<PlatformerObject*>(fixtureA->GetBody()->GetUserData().pointer);
            obj->changeFootContact(-1);
        }

        b2Fixture* fixtureB = contact->GetFixtureB();
        if (fixtureB->IsSensor()) {
            PlatformerObject* obj =
                reinterpret_cast<PlatformerObject*>(fixtureB->GetBody()->GetUserData().pointer);
            obj->changeFootContact(-1);
        }
    }

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {}

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}
};

const int PPM = 100;
const b2Vec2 gravity = b2Vec2(0.0f, 9.8f * PPM);
}; // namespace Box2D

#endif
