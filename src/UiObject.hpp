#pragma once

class UiObject
{
public:
    virtual ~UiObject() = default;
    virtual void draw() = 0;
    virtual void update() = 0;
};
