#pragma once

#include <memory>
#include <vector>

#include "GameState.hpp"
#include "Timer.hpp"

class GameStateManager final
{
public:
    static GameStateManager& Instance();
    GameStateManager(GameStateManager const&) = delete;
    GameStateManager& operator=(GameStateManager const&) = delete;

    void update();
    void render() const;

    void pushState(std::unique_ptr<GameState> state);
    void changeState(std::unique_ptr<GameState> state);
    void popState();

    void clean();

    GameState* getCurrentState() const;

    bool isLoading() const;
    void setLoading(bool is_loading);
    void loading();

private:
    Timer loading_timer_;
    bool is_loading_;
    std::unique_ptr<GameState> loading_state_;
    GameStateManager();
    std::vector<std::unique_ptr<GameState>> states_;
};
