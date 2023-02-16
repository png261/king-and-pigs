#ifndef GAME_STATE_MACHINE_HPP
#define GAME_STATE_MACHINE_HPP

#include <vector>
#include "GameState.hpp"

class GameStateMachine
{
public:
    static GameStateMachine* Instance()
    {
        static GameStateMachine* s_pInstance = new GameStateMachine;
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
    std::vector<GameState*> m_gameStates;
};

#endif
