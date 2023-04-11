#pragma once

class Layer
{
public:
    virtual void render() const = 0;
    virtual void update() = 0;
};
