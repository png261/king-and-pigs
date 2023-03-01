#ifndef PLATFORMER_OBJECT_HPP
#define PLATFORMER_OBJECT_HPP

#include <vector>
#include "Animation.hpp"
#include "DamageableObject.hpp"
#include "GameObject.hpp"
#include "Timer.hpp"

class PlatformerObject : public GameObject
{
public:
    enum direction { DIRECTION_LEFT, DIRECTION_RIGHT };

    enum objectMotion {
        ON_GROUND,
        ON_FLY,
    };

    enum objectStatus {
        ON_NORMAL,
        ON_HIT,
        ON_ATTACK,
        ON_DIE,
    };

    enum ANIMATION_ID {
        IDLE,
        RUN,
        JUMP,
        FALL,
        GROUND,
        ATTACK,
        DEAD,
        HIT,
        DOOR_IN,
        DOOR_OUT,
        DOOR_OPEN,
        DOOR_CLOSE,
    };

    virtual ~PlatformerObject(){};

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual std::string type() const;

    virtual direction getDirection() const;

    virtual bool isFlipped() const;

    virtual void changeFootContact(int n) { m_footContact += n; }

protected:
    PlatformerObject();

    int m_moveSpeed;
    int m_jumpSpeed;
    direction m_direction;

    bool m_bFlipped;

    objectMotion m_currentState;
    objectStatus m_currentAttackState;

    std::map<ANIMATION_ID, Animation*> m_animations;
    ANIMATION_ID m_curAnimation;
    Timer timer;
    b2Fixture* m_pFootSensor;
    int m_footContact;
};

#endif
