#ifndef HEART_HPP
#define HEART_HPP

#include "ItemObject.hpp"

class Heart : public ItemObject
{
public:
    void load(const LoaderParams* pParams);

    void update();
    void clean();
    void bonus();

    std::string type() const { return "Heart"; }
};

#endif
