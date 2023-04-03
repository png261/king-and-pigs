#pragma once

class Layer
{
public:
    virtual ~Layer() = default;

    virtual void render() = 0;
    virtual void update() = 0;
};
