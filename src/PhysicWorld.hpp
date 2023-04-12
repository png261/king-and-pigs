#pragma once

#include <box2d/b2_types.h>
#include <box2d/box2d.h>
#include <memory>
#include "Window.hpp"

class DebugDraw;
class ContactListener;
class PhysicWorld final
{
public:
    enum Category : uint16 {
        CAT_NONE = 0x0000,
        CAT_WALL = 0x0001,
        CAT_ONE_WAY_WALL = 0x0002,
        CAT_PLAYER = 0x0004,
        CAT_DOOR_IN = 0x0008,
        CAT_DOOR_OUT = 0x0010,
        CAT_PIG = 0x0020,
        CAT_BOX = 0x0040,
        CAT_ITEM = 0x0080,
        CAT_BOMB = 0x0100,
        CAT_FOOT_SENSOR = 0x0200,
        CAT_ATTACK_SENSOR = 0x0400,
        CAT_ALL = 0xFFFF,
    };

    enum Mask : uint16 {
        MASK_NONE = CAT_NONE,
        MASK_PLAYER = CAT_ALL,
        MASK_WALL = CAT_ALL,
        MASK_DOOR_OUT = CAT_PLAYER,
        MASK_DOOR_IN = CAT_PLAYER,
        MASK_PIG = CAT_ALL & ~CAT_ITEM,
        MASK_BOX = CAT_ALL & ~CAT_ITEM,
        MASK_ITEM = CAT_PLAYER | CAT_WALL,
        MASK_BOMB = CAT_ALL,
        MASK_FOOT_SENSOR = CAT_ALL,
        MASK_PLAYER_ATTACK_SENSOR = CAT_PIG | CAT_BOX,
        MASK_PIG_ATTACK_SENSOR = CAT_PLAYER,
        MASK_PIG_VISION_SENSOR = CAT_ALL,
    };

    static PhysicWorld& Instance();
    PhysicWorld(PhysicWorld const&) = delete;
    PhysicWorld& operator=(PhysicWorld const&) = delete;

    bool init(Window* const window);
    void update();
    void clean();

    b2Body* createStaticBody(
        const b2Vec2 position,
        const int width,
        const int height,
        const Category category,
        const Mask mask);

    void debugDraw();
    void createContactListener();

    b2World* getWorld();

    static int meterToPixel(float meter);
    static float pixelToMeter(int pixel);

    static b2Vec2 meterToPixel(b2Vec2 meter);
    static b2Vec2 pixelToMeter(b2Vec2 pixel);

    static float radToDeg(float rad);
    static float degToRad(float deg);

    static const b2Vec2 GRAVITY;

private:
    static const float PIXEL_PER_METER;
    static const float METER_PER_PIXEL;
    static const float RAD_PER_DEG;
    static const float DEG_PER_RAD;
    static const float GROUND_FRICTION;

    PhysicWorld();
    void AttackListener(b2Contact* const contact);
    void handleAttack(b2Fixture* const Attacker, b2Fixture* const Defender);
    void DoorInListener(b2Contact* const contact);
    void BombListener(b2Contact* const contact);

    b2World* m_pWorld;
    std::unique_ptr<DebugDraw> m_pDebugDraw;
    std::unique_ptr<ContactListener> m_contactListener;

    float m_timeStep;
    int32 m_velocityIterations;
    int32 m_positionIterations;
};
