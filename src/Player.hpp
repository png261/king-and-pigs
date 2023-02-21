#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "PlatformerObject.hpp"

class Player : public PlatformerObject
{
public:
    void load(const LoaderParams* pParams);

    void draw();
    void update();
    void clean();

    std::string type() const { return "Player"; }

private:
    void handleInput();
    b2Fixture* m_pAttackRange;
};

#endif
