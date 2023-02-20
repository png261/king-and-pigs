#ifndef BOX2D_HPP
#define BOX2D_HPP

#include <box2d/box2d.h>

class DebugDraw;
class Box2D
{
public:
    static Box2D* Instance();
    b2World* init();
    void update();
    void debugDraw();
    b2World* getWorld();
    DebugDraw* getDebugDraw();
    void toggleDebugDraw();

    enum filterCategory {
        PLAYER = 0x0001,
        PLAYER_FOOT = 0x0002,
        WALL = 0x0004,
        ENEMY = 0x0008,
        ITEM = 0x00010,
    };
    static const int PPM;
    static const b2Vec2 GRAVITY;

private:
    Box2D(){};
    b2World* m_pWorld;
    bool m_bDebugEnable;
    DebugDraw* m_pDebugDraw;
};

#endif
