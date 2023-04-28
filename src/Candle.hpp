#pragma once

#include "GameObject.hpp"
#include "ObjectFactory.hpp"

class Candle : public GameObject
{
public:
    void load(std::unique_ptr<LoaderParams> const& params) override;
    void loadAnimation() override;

private:
    enum AnimationID {
        NORMAL,
    };
};

class CandleCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<Candle>(); }
};
