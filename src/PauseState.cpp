#include "PauseState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string PauseState::s_stateID = "PAUSE";

PauseState::PauseState()
    : m_bEnterResume(false)
    , m_bEnterMainMenu(false){};

void PauseState::update()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }

    if (m_bEnterResume) {
        GameStateMachine::Instance().popState();
        return;
    }
    if (m_bEnterMainMenu) {
        GameStateMachine::Instance().popState();
        GameStateMachine::Instance().changeState(new MainMenuState());
        return;
    }

    if (InputHandler::Instance().isKeyDown(KEY_ESCAPE)) {
        m_bEnterResume = true;
    }

    for (const auto& obj : m_uiObjects) {
        obj->update();
    }
};

void PauseState::render() const
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }

    for (const auto& obj : m_uiObjects) {
        obj->draw();
    }
};

bool PauseState::enter()
{
    m_bLoaded = false;
    TextureManager& texture = TextureManager::Instance();
    texture.load(IMAGE_DIRECTORY + "UI/Button/normal.png", "button normal");
    texture.load(IMAGE_DIRECTORY + "UI/Button/hovered.png", "button hovered");
    texture.load(IMAGE_DIRECTORY + "UI/Button/pressed.png", "button pressed");

    Button* resumeButton = new Button(
        "Resume",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2,
        250,
        70);

    Button* mainMenuButton = new Button(
        "Main Menu",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);

    resumeButton->onClick([this]() { m_bEnterResume = true; });
    mainMenuButton->onClick([this]() { m_bEnterMainMenu = true; });

    m_uiObjects.push_back(std::unique_ptr<UiObject>(resumeButton));
    m_uiObjects.push_back(std::unique_ptr<UiObject>(mainMenuButton));

    m_bLoaded = true;
    return true;
};

bool PauseState::exit()
{
    m_bPaused = true;
    InputHandler::Instance().reset();
    return true;
};

std::string PauseState::getStateID() const
{
    return s_stateID;
};
