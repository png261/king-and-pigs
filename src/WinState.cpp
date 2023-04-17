#include "WinState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string WinState::s_stateID = "WIN";

WinState::WinState()
    : m_bEnterMainMenu(false)
    , m_bEnterExit(false){};

void WinState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }


    if (m_bEnterMainMenu) {
        GameStateMachine::Instance().clean();
        GameStateMachine::Instance().changeState(std::make_unique<MainMenuState>());
        return;
    }

    if (m_bEnterExit) {
        Game::Instance().quit();
        return;
    }

    for (const auto& obj : m_uiObjects) {
        obj->update();
    }
};

void WinState::render() const
{
    if (!isLoaded() || isPaused()) {
        return;
    }
    for (const auto& obj : m_uiObjects) {
        obj->draw();
    }
    Game::Instance().getWindow()->print(
        "You are win",
        150,
        Game::Instance().getWindow()->getCenterX(),
        Game::Instance().getWindow()->getCenterY() - 150,
        Color::WHITE);
};

bool WinState::enter()
{
    m_bLoaded = false;

    std::unique_ptr<Button> mainMenuButton = std::make_unique<Button>(
        "Main Menu",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2,
        250,
        70);

    std::unique_ptr<Button> exitButton = std::make_unique<Button>(
        "Exit",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);

    mainMenuButton->onClick([this]() { m_bEnterMainMenu = true; });
    exitButton->onClick([this]() { m_bEnterExit = true; });

    m_uiObjects.push_back(std::move(mainMenuButton));
    m_uiObjects.push_back(std::move(exitButton));

    m_bLoaded = true;

    return true;
};

bool WinState::exit()
{
    pause();
    InputHandler::Instance().reset();
    return true;
};

std::string WinState::getStateID() const
{
    return s_stateID;
};
