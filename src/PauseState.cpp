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

    for (const auto& obj : m_uiObjects) {
        obj->update();
    }
};

void PauseState::render()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }

    for (const auto& obj : m_uiObjects) {
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
    const auto texture = TextureManager::Instance();
    texture->load(ASSETS_DIR + "UI/Button/normal.png", "button normal");
    texture->load(ASSETS_DIR + "UI/Button/hovered.png", "button hovered");
    texture->load(ASSETS_DIR + "UI/Button/pressed.png", "button pressed");

    Button* btn = new Button(
        "Resume",
        Game::Instance()->getWindow()->getCenterX() - 250 / 2,
        Game::Instance()->getWindow()->getCenterY() - 70 / 2,
        250,
        70);
    btn->onClick(s_resume);

    Button* btn2 = new Button(
        "Main Menu",
        Game::Instance()->getWindow()->getCenterX() - 250 / 2,
        Game::Instance()->getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);
    btn2->onClick(s_mainMenu);

    m_uiObjects.push_back(std::unique_ptr<UiObject>(btn));
    m_uiObjects.push_back(std::unique_ptr<UiObject>(btn2));

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
