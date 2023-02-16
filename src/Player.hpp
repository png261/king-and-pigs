#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "PlatformerObject.hpp"
#include "Timer.hpp"

class Player : public PlatformerObject
{
public:
    Player();
    virtual ~Player() {}

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual std::string type() { return "Player"; }

private:
    void ressurect();
    void handleInput();
    Timer timer;
};

#endif
