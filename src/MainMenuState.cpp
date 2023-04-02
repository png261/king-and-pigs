#include "MainMenuState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "Log.hpp"
#include "PauseState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string MainMenuState::s_stateID = "MAIN_MENU";

MainMenuState::MainMenuState(){};

MainMenuState::~MainMenuState()
{
    for (auto& obj : m_uiObjects) {
        delete obj;
        obj = nullptr;
    }
    m_uiObjects.clear();
};

bool MainMenuState::onEnter()
{
    if (this->load() == false) {
        return false;
    }
    return true;
};

void MainMenuState::update()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }

    for (auto& obj : m_uiObjects) {
        obj->update();
    }
};

void MainMenuState::render()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }
    for (auto& obj : m_uiObjects) {
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
    m_bLoaded = false;
    TextureManager* const texture = TextureManager::Instance();
    texture->load(ASSETS_DIR + "UI/Button/normal.png", "button normal");
    texture->load(ASSETS_DIR + "UI/Button/hovered.png", "button hovered");
    texture->load(ASSETS_DIR + "UI/Button/pressed.png", "button pressed");

    Button* btn = new Button("Play", 250, 100, 176, 64);
    btn->setCallback(s_enterPlay);

    Button* btn2 = new Button("Exit", 250, 200, 176, 64);
    btn2->setCallback(s_exit);

    m_uiObjects.push_back(btn);
    m_uiObjects.push_back(btn2);

    m_bLoaded = true;

    return true;
};

bool MainMenuState::onExit()
{
    m_bPaused = true;
    return true;
};

std::string MainMenuState::getStateID() const
{
    return s_stateID;
};
