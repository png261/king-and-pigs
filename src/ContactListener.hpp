#ifndef CONTACT_LISTENER_HPP
#define CONTACT_LISTENER_HPP

#include "Box2D.hpp"

class ContactListener final : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

private:
    void ItemContact(b2Contact* contact);

    void JumpBeginContact(b2Contact* contact);
    void JumpEndContact(b2Contact* contact);
};

#endif
