#ifndef BOX2D_HPP
#define BOX2D_HPP

#include <box2d/box2d.h>

class DebugDraw;
class Box2D
{
public:
    static Box2D* Instance();
    bool init();
    void update();
    void handleEvents();
    void debugDraw();
    b2World* getWorld();
    DebugDraw* getDebugDraw();
    void toggleDebugDraw();

    enum collisionFilterCategory : uint16 {
        CAT_ALL = 0xFFFF,
        CAT_WALL = 0x0001,
        CAT_PLAYER,
        CAT_ENEMY,
        CAT_ITEM,
        CAT_FOOT_SENSOR,
        CAT_ATTACK_SENSOR,
    };

    enum collisionFilterMask : uint16 {
        MASK_PLAYER = CAT_ALL,
        MASK_WALL = CAT_ALL,
        MASK_ENEMY = CAT_ALL,
        MASK_ITEM = CAT_PLAYER | CAT_WALL,
        MASK_FOOT_SENSOR = CAT_ALL,
        MASK_PLAYER_ATTACK_SENSOR = CAT_ENEMY,
        MASK_ENEMY_ATTACK_SENSOR = CAT_PLAYER,
    };

    static const int PPM;
    static const b2Vec2 GRAVITY;

private:
    Box2D();

    b2World* m_pWorld;
    bool m_bDebugEnable;
    DebugDraw* m_pDebugDraw;

    float m_timeStep;
    int32 m_velocityIterations;
    int32 m_positionIterations;
};

#endif
