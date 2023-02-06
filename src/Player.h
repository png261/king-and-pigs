#ifndef PLAYER_H
#define PLAYER_H

#include "PlatformerObject.h"

#include <map>
#include <string>

enum player_state {
    ON_GROUND,
    ON_FLY,
};

class Player : public PlatformerObject {
  public:
    Player();
    virtual ~Player() {}

    virtual void load(const LoaderParams *pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    virtual void collision();

    virtual std::string type() { return "Player"; }

  private:
    // bring the player back if there are lives left
    void ressurect();

    // handle any input from the keyboard, mouse, or joystick
    void handleInput();

    // handle any animation for the player
    void handleAnimation();

    player_state m_currentState;
};

#endif
