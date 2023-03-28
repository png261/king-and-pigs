#pragma once

#include "GameObject.hpp"

class Candle : public GameObject
{
public:
    void load(std::unique_ptr<LoaderParams> const& pParams) override;
    void loadAnimation() override;

private:
    enum animations {
        NORMAL,
    };
};
