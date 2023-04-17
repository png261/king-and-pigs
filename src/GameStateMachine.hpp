#pragma once

#include <memory>
#include <vector>
#include "GameState.hpp"
#include "Timer.hpp"

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

    bool isLoading() const;
    void setLoading(bool bLoading);
    void loading();

private:
    Timer loadingTimer;
    bool m_bLoading;
    std::unique_ptr<GameState> m_loadingState;
    GameStateMachine();
    std::vector<std::unique_ptr<GameState>> m_gameStates;
};
