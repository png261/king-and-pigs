#include "GameStateMachine.hpp"
#include <memory>

#include "LoadingState.hpp"

GameStateMachine::GameStateMachine()
    : loading_timer_(500)
{
    loading_state_ = std::make_unique<LoadingState>();
}

GameStateMachine& GameStateMachine::Instance()
{
    static GameStateMachine instance{};
    return instance;
}

void GameStateMachine::clean()
{
    for (const auto& state : states_) {
        state->exit();
    }
    states_.clear();
}

void GameStateMachine::update()
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

void GameStateMachine::render() const
{
    if (isLoading()) {
        loading_state_->render();
        return;
    }

    for (const auto& state : states_) {
        state->render();
    }
}

void GameStateMachine::pushState(std::unique_ptr<GameState> state)
{
    states_.push_back(std::move(state));
    states_.back()->enter();
}

void GameStateMachine::popState()
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

void GameStateMachine::changeState(std::unique_ptr<GameState> state)
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

GameState* GameStateMachine::getCurrentState()
{
    return states_.back().get();
}

bool GameStateMachine::isLoading() const
{
    return is_loading_;
}

void GameStateMachine::setLoading(bool is_loading)
{
    is_loading_ = is_loading;
}

void GameStateMachine::loading()
{
    setLoading(true);
    loading_timer_.restart();
}
