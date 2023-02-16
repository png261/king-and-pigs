#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "ItemObject.hpp"

class Diamond : public ItemObject
{
public:
    void load(const LoaderParams* pParams);

    void update();
    void clean();
    void bonus();

    std::string type() { return "Diamond"; }
};

#endif
