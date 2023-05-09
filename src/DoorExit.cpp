#include "DoorExit.hpp"

#include "Utils.hpp"

DoorExit::DoorExit() {}

void DoorExit::load(std::unique_ptr<LoaderParams> const& params)
{
    Door::load(std::move(params));
    createSensor();
    setFilterData(ContactCategory::CAT_DOOR_EXIT, ContactMask::MASK_DOOR_EXIT);
}

void DoorExit::createSensor()
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
    sensorDef.filter.categoryBits = ContactCategory::CAT_DOOR_ENTRY;
    sensorDef.filter.maskBits = ContactMask::MASK_DOOR_EXIT;
    body_->CreateFixture(&sensorDef);
}
