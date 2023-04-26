#pragma once

#include <memory>
#include <unordered_map>

#include "Animation.hpp"
#include "LoaderParams.hpp"
#include "PhysicObject.hpp"
#include "PhysicWorld.hpp"
#include "VisionObject.hpp"

class GameObject : public PhysicObject
{
public:
    GameObject();
    virtual ~GameObject() = default;

    virtual void load(std::unique_ptr<LoaderParams> const& params);
    virtual void update();
    virtual void updateAnimation();
    virtual void draw() const;
    virtual void loadAnimation();

    virtual int getWidth() const;
    virtual int getHeight() const;

    virtual bool isExist() const;

    virtual void disappear();

protected:
    enum direction {
        RIGHT = 1,
        LEFT = -1,
    };

    int width_;
    int height_;

    bool is_exist_;
    bool is_flip_;

    direction direction_;

    std::unordered_map<int, std::unique_ptr<Animation>> animations_;
    int current_animation_;
};
