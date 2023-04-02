#include "PauseState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string PauseState::s_stateID = "PAUSE";

PauseState::PauseState(){};

PauseState::~PauseState()
{
    for (auto& obj : m_uiObjects) {
        delete obj;
        obj = nullptr;
    }
    m_uiObjects.clear();
};

bool PauseState::onEnter()
{
    if (this->load() == false) {
        return false;
    }
    return true;
};

void PauseState::update()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }

    if (InputHandler::Instance()->isKeyDown(KEY_ESCAPE)) {
        s_resume();
    }

    for (auto& obj : m_uiObjects) {
        obj->update();
    }
};

void PauseState::render()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }

    for (auto& obj : m_uiObjects) {
        obj->draw();
    }
};

void PauseState::s_resume()
{
    GameStateMachine::Instance()->popState();
}

void PauseState::s_mainMenu()
{
    GameStateMachine::Instance()->changeState(new MainMenuState());
}

bool PauseState::load()
{
    m_bLoaded = false;
    TextureManager* const texture = TextureManager::Instance();
    texture->load(ASSETS_DIR + "UI/Button/normal.png", "button normal");
    texture->load(ASSETS_DIR + "UI/Button/hovered.png", "button hovered");
    texture->load(ASSETS_DIR + "UI/Button/pressed.png", "button pressed");

    Button* btn = new Button("resume", 250, 100, 176, 64);
    btn->setCallback(s_resume);

    Button* btn2 = new Button("main menu", 250, 200, 176, 64);
    btn2->setCallback(s_mainMenu);

    m_uiObjects.push_back(btn);
    m_uiObjects.push_back(btn2);

    m_bLoaded = true;
    return true;
};

bool PauseState::onExit()
{
    m_bPaused = true;
    InputHandler::Instance()->reset();
    return true;
};

std::string PauseState::getStateID() const
{
    return s_stateID;
};
