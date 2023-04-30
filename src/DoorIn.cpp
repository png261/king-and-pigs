#include "DoorIn.hpp"

#include "Utils.hpp"

DoorIn::DoorIn() {}

void DoorIn::load(std::unique_ptr<LoaderParams> const& params)
{
    Door::load(std::move(params));
    createSensor();
    setFilterData(ContactCategory::CAT_DOOR_IN, ContactMask::MASK_DOOR_IN);
}

void DoorIn::createSensor()
{
    float sensorSize = 5;
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(
        Utils::pixelToMeter(sensorSize) * 0.5f,
        Utils::pixelToMeter(sensorSize) * 0.5f,
        b2Vec2(
            Utils::pixelToMeter(width_ / 4.0f - sensorSize),
            Utils::pixelToMeter(height_ / 4.0f - sensorSize)),
        0);

    b2FixtureDef sensorDef;
    sensorDef.shape = &dynamicBox;
    sensorDef.isSensor = true;
    sensorDef.filter.categoryBits = ContactCategory::CAT_DOOR_IN;
    sensorDef.filter.maskBits = ContactMask::MASK_DOOR_IN;
    body_->CreateFixture(&sensorDef);
}
