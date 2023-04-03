#include "GameStateMachine.hpp"

GameStateMachine::GameStateMachine() {}

GameStateMachine::~GameStateMachine() {}

GameStateMachine* GameStateMachine::Instance()
{
    static GameStateMachine* const s_pInstance = new GameStateMachine;
    return s_pInstance;
}

void GameStateMachine::clean()
{
    if (!m_gameStates.empty()) {
        return;
    }

    for (const auto& state : m_gameStates) {
        state->onExit();
        delete state;
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

void GameStateMachine::pushState(GameState* const pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
    if (!m_gameStates.empty()) {
        m_gameStates.back()->onExit();
        m_gameStates.pop_back();
    }

    m_gameStates.back()->resume();
}

void GameStateMachine::changeState(GameState* const pState)
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
    return m_gameStates.back();
}
