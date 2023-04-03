#pragma once

#include <memory>
#include <vector>
#include "GameState.hpp"

class GameStateMachine final
{
public:
    static std::shared_ptr<GameStateMachine> Instance();
    GameStateMachine(GameStateMachine const&) = delete;
    GameStateMachine& operator=(GameStateMachine const&) = delete;

    void update();
    void render();

    void pushState(GameState* const pState);
    void changeState(GameState* const pState);
    void popState();

    GameState* getCurrentState();

    void clean();

private:
    GameStateMachine() = default;
    std::vector<GameState*> m_gameStates;
};
