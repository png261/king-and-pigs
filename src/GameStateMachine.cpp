#include "GameStateMachine.hpp"

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
    if (!m_gameStates.empty()) {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render() const
{
    for (const auto& state : m_gameStates) {
        state->render();
    }
}

void GameStateMachine::pushState(GameState* const pState)
{
    m_gameStates.push_back(std::unique_ptr<GameState>(pState));
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

void GameStateMachine::changeState(GameState* const pState)
{
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID()) {
            return;
        }

        m_gameStates.back()->exit();
        m_gameStates.pop_back();
    }

    pState->enter();
    m_gameStates.push_back(std::unique_ptr<GameState>(pState));
}

GameState* GameStateMachine::getCurrentState()
{
    return m_gameStates.back().get();
}
