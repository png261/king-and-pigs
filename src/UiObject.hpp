#pragma once

#include <memory>
#include "LoaderParams.hpp"

class UiObject
{
public:
    virtual ~UiObject();

    virtual void load(std::unique_ptr<LoaderParams> const& pParams);
    virtual void draw() = 0;
    virtual void update() = 0;
};
