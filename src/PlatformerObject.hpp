#ifndef PLATFORMER_OBJECT_HPP
#define PLATFORMER_OBJECT_HPP

#include <map>
#include "Animation.hpp"
#include "GameObject.hpp"

class PlatformerObject : public GameObject
{
public:
    enum ObjectPosition {
        ON_GROUND,
        ON_FLY,
    };

    enum ObjectState {
        ON_NORMAL,
        ON_HIT,
        ON_ATTACK,
        ON_DIE,
    };

    virtual ~PlatformerObject(){};

    virtual void load(const LoaderParams* const pParams);

    virtual void draw();
    virtual void update();

    virtual void changeFootContact(int n);

protected:
    PlatformerObject();

    int m_moveSpeed;
    int m_jumpSpeed;

    bool m_bFlipped;

    ObjectPosition m_currentState;
    ObjectState m_currentAttackState;

    std::map<Animation::AnimationID, Animation*> m_animations;
    Animation::AnimationID m_curAnimation;

    b2Fixture* m_pFootSensor;
    int m_footContact;
};

#endif
