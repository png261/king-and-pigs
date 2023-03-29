#include "MainMenuState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string MainMenuState::s_stateID = "MAIN_MENU";

MainMenuState::MainMenuState(){};

MainMenuState::~MainMenuState(){};

bool MainMenuState::onEnter()
{
    m_loadingComplete = false;

    if (this->load() == false) {
        return false;
    }

    m_loadingComplete = true;
    return true;
};

void MainMenuState::update()
{
    if (!m_loadingComplete || m_exiting) {
        return;
    }

    for (auto& obj : m_uiObjects) {
        if (obj == nullptr) {
            continue;
        }
        obj->update();
    }
};

void MainMenuState::render()
{
    if (!m_loadingComplete || m_exiting) {
        return;
    }
    for (auto& obj : m_uiObjects) {
        if (obj == nullptr) {
            continue;
        }
        obj->draw();
    }
};

void MainMenuState::s_enterPlay()
{
    GameStateMachine::Instance()->changeState(new PlayState());
}

void MainMenuState::s_exit()
{
    Game::Instance()->quit();
}

bool MainMenuState::load()
{
    TextureManager* const texture = TextureManager::Instance();
    texture->load(ASSETS_DIR + "UI/Button/normal.png", "button normal");
    texture->load(ASSETS_DIR + "UI/Button/hovered.png", "button hovered");
    texture->load(ASSETS_DIR + "UI/Button/pressed.png", "button pressed");

    Button* btn = new Button(100, 100, 176, 64);
    btn->setCallback(s_enterPlay);

    Button* btn2 = new Button(100, 100, 176, 64);
    btn2->setCallback(s_exit);

    m_uiObjects.push_back(btn);
    m_uiObjects.push_back(btn2);

    return true;
};

void MainMenuState::resume()
{
    m_exiting = false;
};

bool MainMenuState::onExit()
{
    m_exiting = true;
    return true;
};

std::string MainMenuState::getStateID() const
{
    return s_stateID;
};
