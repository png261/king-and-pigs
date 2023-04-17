#include "GameState.hpp"

void GameState::resume()
{
    m_bPaused = false;
};

void GameState::pause()
{
    m_bPaused = true;
};

bool GameState::isLoaded() const
{
    return m_bLoaded;
}

bool GameState::isPaused() const
{
    return m_bPaused;
}
