#pragma once

#include "Object.hpp"

class UiObject : public Object
{
public:
    virtual ~UiObject() = default;
    virtual void load(std::unique_ptr<LoaderParams> const& params) = 0;
    virtual void update() = 0;
    virtual void draw() const = 0;
};
