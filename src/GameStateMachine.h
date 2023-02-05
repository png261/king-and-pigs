#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "GameState.h"
#include <vector>

class GameStateMachine {
  public:
    static GameStateMachine *Instance() {
        static GameStateMachine *s_pInstance = new GameStateMachine;
        return s_pInstance;
    }

    void update();
    void render();

    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();

    void clean();

  private:
    GameStateMachine(){};
    std::vector<GameState *> m_gameStates;
};

#endif
