#pragma once

#include "GameObject.hpp"

class Decor : public GameObject
{
public:
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void loadAnimation() override;
};
