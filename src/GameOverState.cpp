#include "GameOverState.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"
#include "MenuButton.hpp"
#include "PlayState.hpp"
#include "StateParser.hpp"
#include "TextureManager.hpp"
#include "Log.hpp"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
    GameStateMachine::Instance()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
    GameStateMachine::Instance()->changeState(new PlayState());
}

void GameOverState::update()
{
    if (m_loadingComplete && !m_gameObjects.empty()) {
        for (auto& obj : m_gameObjects) {
            obj->update();
        }
    }
}

void GameOverState::render()
{
    if (m_loadingComplete && !m_gameObjects.empty()) {
        for (int i = 0; i < m_gameObjects.size(); i++) {
            m_gameObjects[i]->draw();
        }
    }
}

bool GameOverState::onEnter()
{
    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/states.xml", s_gameOverID, &m_gameObjects);

    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    // set the callbacks for menu items
    setCallbacks(m_callbacks);

    m_loadingComplete = true;

    Log::log("entering GameOverState");
    return true;
}

bool GameOverState::onExit()
{
    m_exiting = true;
    m_gameObjects.clear();

    TheInputHandler::Instance()->reset();

    Log::log("exiting GameOverState");
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
    for (auto& obj : m_gameObjects) {
        if (dynamic_cast<MenuButton*>(obj)) {
            MenuButton* pButton = dynamic_cast<MenuButton*>(obj);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}
