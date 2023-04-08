#include "GameStateMachine.hpp"

std::shared_ptr<GameStateMachine> GameStateMachine::Instance()
{
    static std::shared_ptr<GameStateMachine> s_pInstance{new GameStateMachine};
    return s_pInstance;
}

void GameStateMachine::clean()
{
    for (const auto& state : m_gameStates) {
        state->onExit();
    }
    m_gameStates.clear();
}

void GameStateMachine::update()
{
    if (!m_gameStates.empty()) {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render()
{
    for (const auto& state : m_gameStates) {
        state->render();
    }
}

void GameStateMachine::pushState(std::shared_ptr<GameState> const& pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
    if (m_gameStates.empty()) {
        return;
    }

    m_gameStates.back()->onExit();
    m_gameStates.pop_back();
    if (!m_gameStates.empty()) {
        m_gameStates.back()->resume();
    }
}

void GameStateMachine::changeState(std::shared_ptr<GameState> const& pState)
{
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID()) {
            return;
        }

        m_gameStates.back()->onExit();
        m_gameStates.pop_back();
    }

    pState->onEnter();
    m_gameStates.push_back(pState);
}

GameState* GameStateMachine::getCurrentState()
{
    return m_gameStates.back().get();
}
