#pragma once

#include <box2d/b2_types.h>
#include <box2d/box2d.h>

class DebugDraw;
class ContactListener;
class PhysicWorld final
{
public:
    static PhysicWorld* Instance();
    bool init();
    void clean();
    void update();

    void handleEvents();
    void contactListener();
    void debugDraw();
    void toggleDebugDraw();

    b2World* getWorld();

    enum FilterCategory : uint16 {
        CAT_WALL = 0x0001,
        CAT_ONE_WAY_WALL = 0x0002,
        CAT_PLAYER = 0x0004,
        CAT_DOOR_IN = 0x0008,
        CAT_DOOR_OUT = 0x0010,
        CAT_ENEMY = 0x0020,
        CAT_ITEM = 0x0040,
        CAT_FOOT_SENSOR = 0x0080,
        CAT_ATTACK_SENSOR = 0x0100,
        CAT_ENEMY_VISION_SENSOR = 0x0200,
        CAT_ALL = 0xFFFF,
        CAT_NONE = 0x0000,
    };

    enum FilterMask : uint16 {
        MASK_PLAYER = CAT_ALL,
        MASK_WALL = CAT_ALL,
        MASK_DOOR_OUT = CAT_PLAYER,
        MASK_DOOR_IN = CAT_PLAYER,
        MASK_ENEMY = CAT_ALL & ~CAT_ITEM,
        MASK_ITEM = CAT_PLAYER | CAT_WALL,
        MASK_FOOT_SENSOR = CAT_ALL,
        MASK_PLAYER_ATTACK_SENSOR = CAT_ENEMY,
        MASK_ENEMY_ATTACK_SENSOR = CAT_PLAYER,
        MASK_ENEMY_VISION_SENSOR = CAT_ALL,
    };

    void createCollisionObject(
        PhysicWorld::FilterCategory categoyr,
        const int width,
        const int height,
        b2Vec2 position);

    static const float PIXEL_PER_METER;
    static const float METER_PER_PIXEL;
    static const float RAD_PER_DEG;
    static const float DEG_PER_RAD;
    static const float GROUND_FRICTION;
    static const b2Vec2 GRAVITY;

    static int meterToPixel(float meter);
    static float pixelToMeter(float pixel);

    static b2Vec2 meterToPixel(b2Vec2 meter);
    static b2Vec2 pixelToMeter(b2Vec2 pixel);

    static float radToDeg(float rad);
    static float degToRad(float deg);

private:
    PhysicWorld();
    void AttackListener(b2Contact* contact);
    void enemyVisionListener(b2Contact* contact);
    void handleAttack(b2Fixture* Attacker, b2Fixture* Defender);
    void DoorInListener(b2Contact* contact);

    b2World* m_pWorld;
    bool m_bDebugEnable;
    DebugDraw* m_pDebugDraw;
    ContactListener* m_contactListener;

    float m_timeStep;
    int32 m_velocityIterations;
    int32 m_positionIterations;
};
