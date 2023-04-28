#pragma once

#include <memory>

#include "LoaderParams.hpp"
#include "PhysicWorld.hpp"

class Object
{
public:
    Object();
    virtual ~Object() = default;

    virtual void load(std::unique_ptr<LoaderParams> const& params);
    virtual void update() = 0;
    virtual void draw() const = 0;

    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual b2Vec2 getPosition() const;
    virtual bool isExist() const;
    virtual void disappear();

protected:
    bool is_exist_;
    b2Vec2 position_;
    int width_;
    int height_;
};
