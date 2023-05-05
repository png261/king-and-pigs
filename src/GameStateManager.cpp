#include "GameStateManager.hpp"

#include <memory>

#include "LoadingState.hpp"

GameStateManager::GameStateManager()
    : loading_timer_(500)
{
    loading_state_ = std::make_unique<LoadingState>();
}

GameStateManager& GameStateManager::Instance()
{
    static GameStateManager instance{};
    return instance;
}

void GameStateManager::clean()
{
    for (const auto& state : states_) {
        state->exit();
    }
    states_.clear();
}

void GameStateManager::update()
{
    if (isLoading()) {
        if (loading_timer_.isDone() && states_.back()->isLoaded()) {
            setLoading(false);
        }
        return;
    }

    if (!states_.empty()) {
        states_.back()->update();
    }
}

void GameStateManager::render() const
{
    if (isLoading()) {
        loading_state_->render();
        return;
    }

    for (const auto& state : states_) {
        state->render();
    }
}

void GameStateManager::pushState(std::unique_ptr<GameState> state)
{
    states_.push_back(std::move(state));
    states_.back()->enter();
}

void GameStateManager::popState()
{
    if (states_.empty()) {
        return;
    }

    states_.back()->exit();
    states_.pop_back();
    if (!states_.empty()) {
        states_.back()->resume();
    }
}

void GameStateManager::changeState(std::unique_ptr<GameState> state)
{
    if (!states_.empty()) {
        if (states_.back()->getStateID() == state->getStateID()) {
            return;
        }

        states_.back()->exit();
        states_.pop_back();
    }

    state->enter();
    states_.push_back(std::move(state));
}

GameState* GameStateManager::getCurrentState() const
{
    return states_.back().get();
}

bool GameStateManager::isLoading() const
{
    return is_loading_;
}

void GameStateManager::setLoading(bool is_loading)
{
    is_loading_ = is_loading;
}

void GameStateManager::loading()
{
    setLoading(true);
    loading_timer_.restart();
}
