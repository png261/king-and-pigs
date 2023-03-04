#ifndef DOOR_OBJECT_HPP
#define DOOR_OBJECT_HPP

#include "GameObject.hpp"

class Door : public GameObject
{
public:
    Door();
    void load(const LoaderParams* const pParams);
    void update();
    void loadAnimation();
};

#endif
