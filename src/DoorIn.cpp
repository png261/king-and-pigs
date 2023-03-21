#include "DoorIn.hpp"
#include "Game.hpp"
#include "Log.hpp"

DoorIn::DoorIn() {}

void DoorIn::load(std::unique_ptr<LoaderParams> const& pParams)
{
    Door::load(std::move(pParams));
    this->createSensor();
    b2Filter filter;
    filter.categoryBits = PhysicWorld::CAT_DOOR_IN;
    filter.maskBits = PhysicWorld::MASK_DOOR_IN;
    m_pFixture->SetFilterData(filter);
}

void DoorIn::createSensor()
{
    float sensorSize = 5;
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(
        PhysicWorld::pixelToMeter(sensorSize) / 2.0f,
        PhysicWorld::pixelToMeter(sensorSize) / 2.0f,
        b2Vec2(
            PhysicWorld::pixelToMeter(m_width / 4.0f - sensorSize),
            PhysicWorld::pixelToMeter(m_height / 4.0f - sensorSize)),
        0);

    b2FixtureDef sensorDef;
    sensorDef.shape = &dynamicBox;
    sensorDef.isSensor = true;
    sensorDef.filter.categoryBits = PhysicWorld::CAT_DOOR_IN;
    sensorDef.filter.maskBits = PhysicWorld::MASK_DOOR_IN;
    m_pBody->CreateFixture(&sensorDef);
}
