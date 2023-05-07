#pragma once

#include "ItemObject.hpp"
#include "ObjectFactory.hpp"

class Heart final : public ItemObject
{
public:
    void load(std::unique_ptr<LoaderParams> const& params) override;
    void update() override;
    void bonus() override;
    void loadAnimation() override;

private:
    enum AnimationID { NORMAL, HIT };
};

class HeartCreator : public BaseCreator
{
    std::unique_ptr<Object> create() const { return std::make_unique<Heart>(); }
};
