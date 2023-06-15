#include "GameState.hpp"

void GameState::resume()
{
    is_paused_ = false;
};

void GameState::pause()
{
    is_paused_ = true;
};

bool GameState::isLoaded() const
{
    return is_loaded_;
}

bool GameState::isPaused() const
{
    return is_paused_;
}
