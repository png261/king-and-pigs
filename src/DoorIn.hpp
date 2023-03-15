#pragma once

#include "Door.hpp"

class DoorIn : public Door
{
public:
    DoorIn();
    void load(const LoaderParams* const pParams);
    void createSensor();
    void open();
    bool isOpened();

private:
    bool m_bOpened;
};
