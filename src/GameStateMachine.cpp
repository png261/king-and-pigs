#include "GameStateMachine.hpp"
#include <memory>

#include "LoadingState.hpp"

GameStateMachine::GameStateMachine()
    : loadingTimer(500)
{
    m_loadingState = std::make_unique<LoadingState>();
}

GameStateMachine& GameStateMachine::Instance()
{
    static GameStateMachine s_instance{};
    return s_instance;
}

void GameStateMachine::clean()
{
    for (const auto& state : m_gameStates) {
        state->exit();
    }
    m_gameStates.clear();
}

void GameStateMachine::update()
{
    if (isLoading()) {
        if (loadingTimer.isDone() && m_gameStates.back()->isLoaded()) {
            setLoading(false);
        }
        return;
    }

    if (!m_gameStates.empty()) {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render() const
{
    if (isLoading()) {
        m_loadingState->render();
        return;
    }

    for (const auto& state : m_gameStates) {
        state->render();
    }
}

void GameStateMachine::pushState(std::unique_ptr<GameState> pState)
{
    m_gameStates.push_back(std::move(pState));
    m_gameStates.back()->enter();
}

void GameStateMachine::popState()
{
    if (m_gameStates.empty()) {
        return;
    }

    m_gameStates.back()->exit();
    m_gameStates.pop_back();
    if (!m_gameStates.empty()) {
        m_gameStates.back()->resume();
    }
}

void GameStateMachine::changeState(std::unique_ptr<GameState> pState)
{
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID()) {
            return;
        }

        m_gameStates.back()->exit();
        m_gameStates.pop_back();
    }

    pState->enter();
    m_gameStates.push_back(std::move(pState));
}

GameState* GameStateMachine::getCurrentState()
{
    return m_gameStates.back().get();
}

bool GameStateMachine::isLoading() const
{
    return m_bLoading;
}

void GameStateMachine::setLoading(bool bLoading)
{
    m_bLoading = bLoading;
}

void GameStateMachine::loading()
{
    setLoading(true);
    loadingTimer.restart();
}
