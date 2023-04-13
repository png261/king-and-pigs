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

    virtual void load(std::unique_ptr<LoaderParams> const& pParams);
    virtual void update();
    virtual void updateAnimation();
    virtual void draw();
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

    int m_width;
    int m_height;

    bool m_bExist;
    bool m_bFlipped;

    direction m_direction;

    std::unordered_map<int, std::unique_ptr<Animation>> m_animations;
    int m_curAnimation;
};
