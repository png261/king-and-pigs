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

    void pushState(std::shared_ptr<GameState> const& pState);
    void changeState(std::shared_ptr<GameState> const& pState);
    void popState();

    GameState* getCurrentState();

    void clean();

private:
    GameStateMachine() = default;
    std::vector<std::shared_ptr<GameState>> m_gameStates;
};
