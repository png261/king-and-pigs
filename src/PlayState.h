#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <vector>
#include "GameState.h"
#include "GameObject.h"

class PlayState : public GameState {
  public:
    virtual void update();
    virtual void render();

    virtual void exit();
    virtual void resume();
    virtual void enter();
    virtual std::string getStateID() const { return s_stateID; }

  private:
    static const std::string s_stateID;
    std::vector<GameObject *> m_gameObjects;
};

#endif
