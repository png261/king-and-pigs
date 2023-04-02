#include "LoseState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string LoseState::s_stateID = "WIN";

LoseState::LoseState(){};

LoseState::~LoseState(){};

bool LoseState::onEnter()
{
    if (this->load() == false) {
        return false;
    }
    return true;
};

void LoseState::update()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }

    for (auto& obj : m_uiObjects) {
        obj->update();
    }
};

void LoseState::render()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }
    for (auto& obj : m_uiObjects) {
        obj->draw();
    }

    Game::Instance()->getWindow()->print("you are died", 40, 320, 50, {});
};

void LoseState::s_mainMenu()
{
    GameStateMachine::Instance()->changeState(new MainMenuState());
}

void LoseState::s_exit()
{
    Game::Instance()->quit();
}

bool LoseState::load()
{
    m_bLoaded = false;
    TextureManager* const texture = TextureManager::Instance();
    texture->load(ASSETS_DIR + "UI/Button/normal.png", "button normal");
    texture->load(ASSETS_DIR + "UI/Button/hovered.png", "button hovered");
    texture->load(ASSETS_DIR + "UI/Button/pressed.png", "button pressed");

    Button* btn = new Button("MainMenu", 250, 100, 176, 64);
    btn->setCallback(s_mainMenu);

    Button* btn2 = new Button("Exit", 250, 200, 176, 64);
    btn2->setCallback(s_exit);

    m_uiObjects.push_back(btn);
    m_uiObjects.push_back(btn2);

    m_bLoaded = true;

    return true;
};

bool LoseState::onExit()
{
    m_bPaused = true;
    return true;
};

std::string LoseState::getStateID() const
{
    return s_stateID;
};
