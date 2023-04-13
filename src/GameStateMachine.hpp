#pragma once

#include <memory>
#include <vector>
#include "GameState.hpp"

class GameStateMachine final
{
public:
    static GameStateMachine& Instance();
    GameStateMachine(GameStateMachine const&) = delete;
    GameStateMachine& operator=(GameStateMachine const&) = delete;

    void update();
    void render() const;

    void pushState(std::unique_ptr<GameState> pState);
    void changeState(std::unique_ptr<GameState> pState);
    void popState();

    GameState* getCurrentState();

    void clean();

private:
    GameStateMachine() = default;
    std::vector<std::unique_ptr<GameState>> m_gameStates;
};
