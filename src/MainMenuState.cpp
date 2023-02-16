#include "MainMenuState.hpp"
#include <iostream>
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "MenuButton.hpp"
#include "PlayState.hpp"
#include "StateParser.hpp"
#include "TextureManager.hpp"

const std::string MainMenuState::s_stateID = "MENU";

// Callbacks
void MainMenuState::s_menuToPlay()
{
    GameStateMachine::Instance()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    TheGame::Instance()->quit();
}

// end callbacks

void MainMenuState::update()
{
    if (!m_loadingComplete || m_exiting) {
        return;
    }
    for (auto& obj : m_gameObjects) {
        obj->update();
    }
}

void MainMenuState::render()
{
    if (!m_loadingComplete || m_exiting) {
        return;
    }

    for (auto& obj : m_gameObjects) {
        obj->draw();
    }
}

bool MainMenuState::onEnter()
{
    GameObjectFactory::Instance()->registerType("MenuButton", new Creator<MenuButton>);

    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/states.xml", s_stateID, &m_gameObjects);

    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    // set the callbacks for menu items
    setCallbacks(m_callbacks);

    m_loadingComplete = true;
    std::cout << "entering MenuState\n";
    return true;
}

bool MainMenuState::onExit()
{
    m_exiting = true;
    m_gameObjects.clear();

    TheInputHandler::Instance()->reset();

    std::cout << "exiting MenuState\n";
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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
