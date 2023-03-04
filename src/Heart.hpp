#ifndef HEART_HPP
#define HEART_HPP

#include <iostream>
#include "ItemObject.hpp"

class Heart : public ItemObject
{
public:
    void load(const LoaderParams* const pParams);

    void update();
    void bonus();
    void loadAnimation();
};

#endif
