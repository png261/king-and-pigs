#include "Object.hpp"


Object::Object()
    : is_exist_(true)
    , width_(0)
    , height_(0)
{}

void Object::load(std::unique_ptr<LoaderParams> const& params)
{
    position_ = b2Vec2(params->x(), params->y());
    width_ = params->width();
    height_ = params->height();
};

void Object::disappear()
{
    is_exist_ = false;
}

bool Object::isExist() const
{
    return is_exist_;
}

int Object::getWidth() const
{
    return width_;
}

int Object::getHeight() const
{
    return height_;
}

b2Vec2 Object::getPosition() const
{
    return position_;
}
