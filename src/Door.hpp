#pragma once

#include "GameObject.hpp"

class Door : public GameObject
{
public:
    Door();
    virtual void load(std::unique_ptr<LoaderParams> const& pParams) override;
    virtual void update() override;
    virtual void loadAnimation() override;

    virtual void open();
    virtual void close();
};
