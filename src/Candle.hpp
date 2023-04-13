#pragma once

#include "GameObject.hpp"
#include "GameObjectFactory.hpp"

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

class CandleCreator : public BaseCreator
{
    std::unique_ptr<GameObject> create() const { return std::make_unique<Candle>(); }
};
