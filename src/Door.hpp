#pragma once

#include "GameObject.hpp"

class Door : public GameObject
{
public:
    Door();
    virtual void load(std::unique_ptr<LoaderParams> const& pParams);
    virtual void update();
    virtual void loadAnimation();
    virtual void open();
    virtual void close();
};
