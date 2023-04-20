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

    void pushState(std::unique_ptr<GameState> state);
    void changeState(std::unique_ptr<GameState> state);
    void popState();

    GameState* getCurrentState();

    void clean();

    bool isLoading() const;
    void setLoading(bool is_loading);
    void loading();

private:
    Timer loading_timer_;
    bool is_loading_;
    std::unique_ptr<GameState> loading_state_;
    GameStateMachine();
    std::vector<std::unique_ptr<GameState>> states_;
};
