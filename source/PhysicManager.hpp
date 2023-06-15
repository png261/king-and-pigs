#pragma once

#include <box2d/box2d.h>

#include <memory>

#include "ContactListener.hpp"
#include "DebugDraw.hpp"
#include "Window.hpp"

enum ContactCategory : uint16 {
    CAT_NONE = 0x0000,
    CAT_WALL = 0x0001,
    CAT_ONE_WAY_WALL = 0x0002,
    CAT_PLAYER = 0x0004,
    CAT_DOOR_ENTRY = 0x0008,
    CAT_DOOR_EXIT = 0x0010,
    CAT_PIG = 0x0020,
    CAT_BOX = 0x0040,
    CAT_ITEM = 0x0080,
    CAT_BOMB = 0x0100,
    CAT_FOOT_SENSOR = 0x0200,
    CAT_ATTACK_SENSOR = 0x0400,
    CAT_ALL = 0xFFFF,
};

enum ContactMask : uint16 {
    MASK_NONE = CAT_NONE,
    MASK_PLAYER = CAT_ALL,
    MASK_WALL = CAT_ALL,
    MASK_DOOR_ENTRY = CAT_PLAYER,
    MASK_DOOR_EXIT = CAT_PLAYER,
    MASK_PIG = CAT_ALL & ~CAT_ITEM,
    MASK_BOX = CAT_ALL & ~CAT_ITEM,
    MASK_ITEM = CAT_PLAYER | CAT_WALL,
    MASK_BOMB = CAT_ALL,
    MASK_FOOT_SENSOR = CAT_ALL,
    MASK_PLAYER_ATTACK_SENSOR = CAT_PIG | CAT_BOX,
    MASK_PIG_ATTACK_SENSOR = CAT_PLAYER,
    MASK_PIG_VISION_SENSOR = CAT_ALL,
};

class PhysicManager final
{
public:
    static PhysicManager& Instance();
    PhysicManager(PhysicManager const&) = delete;
    PhysicManager& operator=(PhysicManager const&) = delete;

    void init(Window* const window);
    void update();
    void clean();
    void debugDraw() const;
    void createContactListener();
    b2World* getWorld() const;

    b2Body* createStaticBody(
        const b2Vec2& position,
        const int width,
        const int height,
        const ContactCategory category,
        const ContactMask mask) const;

private:
    PhysicManager();

    std::unique_ptr<b2World> world_;
    std::unique_ptr<DebugDraw> debugDraw_;
    std::unique_ptr<ContactListener> contactListener_;

    float time_step_;
    int32 velocity_iterations_;
    int32 position_iterations_;
};
