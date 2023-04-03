#pragma once

#include <unordered_map>
#include <memory>
#include "Animation.hpp"
#include "LoaderParams.hpp"
#include "PhysicObject.hpp"
#include "PhysicWorld.hpp"
#include "VisionObject.hpp"

class GameObject : public PhysicObject
{
public:
    virtual ~GameObject();

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
    GameObject();
    enum direction {
        RIGHT = 1,
        LEFT = -1,
    };

    direction m_direction;

    int m_width;
    int m_height;

    bool m_bFlipped;
    bool m_bExist;

    std::unordered_map<int, Animation*> m_animations;
    int m_curAnimation;
};
