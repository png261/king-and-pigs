#include "PauseState.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string PauseState::s_stateID = "PAUSE";

void PauseState::s_pauseToMain()
{
    GameStateMachine::Instance()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
    GameStateMachine::Instance()->popState();
}

void PauseState::update()
{
    if (!m_loadingComplete || m_gameObjects.empty()) {
        return;
    }
    for (auto& obj : m_gameObjects) {
        obj->update();
    }
}

void PauseState::render()
{
    if (!m_loadingComplete || m_gameObjects.empty()) {
        return;
    }
    for (auto& obj : m_gameObjects) {
        obj->draw();
    }
}

bool PauseState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("assets/states.xml", s_stateID, &m_gameObjects);

    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);

    m_loadingComplete = true;

    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::onExit()
{
    if (m_loadingComplete && !m_gameObjects.empty()) {
        for (auto& obj : m_gameObjects) {
            obj->clean();
            delete obj;
        }
        m_gameObjects.clear();
    }
    TheInputHandler::Instance()->reset();

    std::cout << "exiting PauseState\n";
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
    if (m_gameObjects.empty()) {
        return;
    }
    for (auto& obj : m_gameObjects) {
        if (dynamic_cast<MenuButton*>(obj)) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(obj);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}
