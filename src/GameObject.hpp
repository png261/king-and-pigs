#pragma once

#include <map>
#include <memory>
#include "Animation.hpp"
#include "LoaderParams.hpp"
#include "PhysicObject.hpp"
#include "PhysicWorld.hpp"

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

    virtual bool isUpdating() const;
    virtual bool isExist() const;

    virtual void setUpdating(const bool bUpdating);
    virtual void disappear();

protected:
    GameObject();

    int m_width;
    int m_height;

    bool m_bUpdating;
    bool m_bFlipped;
    bool m_bExist;

    std::map<Animation::AnimationID, std::unique_ptr<Animation>> m_animations;
    Animation::AnimationID m_curAnimation;
};
