#include "GameStateMachine.h"

void GameStateMachine::clean() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->exit();

        delete m_gameStates.back();

        m_gameStates.clear();
    }
}

void GameStateMachine::update() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->update();
    }
}

void GameStateMachine::render() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->render();
    }
}

void GameStateMachine::pushState(GameState *pState) {
    m_gameStates.push_back(pState);
    m_gameStates.back()->enter();
}

void GameStateMachine::popState() {
    if (!m_gameStates.empty()) {
        m_gameStates.back()->exit();
        m_gameStates.pop_back();
    }

    m_gameStates.back()->resume();
}

void GameStateMachine::changeState(GameState *pState) {
    if (!m_gameStates.empty()) {
        if (m_gameStates.back()->getStateID() == pState->getStateID()) {
            return; // do nothing
        }

        m_gameStates.back()->exit();
        m_gameStates.pop_back();
    }

    // initialise it
    pState->enter();

    // push back our new state
    m_gameStates.push_back(pState);
}
