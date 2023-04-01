#pragma once

#include <vector>
#include "GameState.hpp"

class GameStateMachine final
{
public:
    static GameStateMachine* Instance();

    void update();
    void render();

    void pushState(GameState* const pState);
    void changeState(GameState* const pState);
    void popState();

    GameState* getCurrentState();

    void clean();

private:
    GameStateMachine(){};
    std::vector<GameState*> m_gameStates;
};
