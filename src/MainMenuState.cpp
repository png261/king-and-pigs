#include "MainMenuState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "PauseState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string MainMenuState::s_stateID = "MAIN_MENU";

MainMenuState::MainMenuState()
    : m_bEnterPlayState(false)
    , m_bEnterQuit(false){};

void MainMenuState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (m_bEnterPlayState) {
        Game::Instance().setLevelIndex(0);
        GameStateMachine::Instance().loading();
        GameStateMachine::Instance().changeState(std::make_unique<PlayState>());
        return;
    }

    if (m_bEnterQuit) {
        Game::Instance().quit();
        return;
    }

    for (const auto& obj : m_uiObjects) {
        obj->update();
    }
};

void MainMenuState::render() const
{
    if (!isLoaded() || isPaused()) {
        return;
    }
    for (const auto& obj : m_uiObjects) {
        obj->draw();
    }
    Game::Instance().getWindow()->print(
        "King and Pigs",
        150,
        Game::Instance().getWindow()->getCenterX(),
        Game::Instance().getWindow()->getCenterY() - 150,
        Color::WHITE);
};

bool MainMenuState::enter()
{
    m_bLoaded = false;

    std::unique_ptr<Button> newGameButton = std::make_unique<Button>(
        "New Game",
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

    newGameButton->onClick([this]() { m_bEnterPlayState = true; });
    exitButton->onClick([this]() { m_bEnterQuit = true; });

    m_uiObjects.push_back(std::move(newGameButton));
    m_uiObjects.push_back(std::move(exitButton));

    m_bLoaded = true;
    return true;
};

bool MainMenuState::exit()
{
    pause();
    InputHandler::Instance().reset();
    return true;
};

std::string MainMenuState::getStateID() const
{
    return s_stateID;
};
