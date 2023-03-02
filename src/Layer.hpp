#ifndef LAYER_HPP
#define LAYER_HPP

class Level;

class Layer
{
public:
    virtual ~Layer() {}

    virtual void render() = 0;
    virtual void update(Level* const pLevel) = 0;
};

#endif
