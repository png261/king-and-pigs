#pragma once

#include <memory>
#include <unordered_map>

#include "Animation.hpp"
#include "LoaderParams.hpp"
#include "Object.hpp"
#include "PhysicObject.hpp"
#include "PhysicManager.hpp"
#include "VisionObject.hpp"

class GameObject : public PhysicObject
{
public:
    GameObject();
    virtual ~GameObject() = default;

    virtual void update() override;
    virtual void updateAnimation();
    virtual void draw() const override;
    virtual void loadAnimation();

protected:
    enum Direction {
        RIGHT = 1,
        LEFT = -1,
    };

    bool is_flip_;

    Direction direction_;

    std::unordered_map<int, std::unique_ptr<Animation>> animations_;
    int current_animation_;
};
