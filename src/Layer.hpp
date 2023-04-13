#pragma once

class Layer
{
public:
    virtual ~Layer() = default;
    virtual void render() const = 0;
    virtual void update() = 0;
};
