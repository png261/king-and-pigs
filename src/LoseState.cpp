#include "LoseState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string LoseState::s_stateID = "LOSE";

LoseState::LoseState()
    : m_bEnterMainMenu(false)
    , m_bEnterExit(false){};

void LoseState::update()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }

    if (m_bEnterRespawn) {
        Game::Instance().useDiamond(2);
        GameStateMachine::Instance().changeState(std::make_unique<PlayState>());
        return;
    }

    if (m_bEnterMainMenu) {
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

void LoseState::render() const
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }
    for (const auto& obj : m_uiObjects) {
        obj->draw();
    }

    Game::Instance().getWindow()->print(
        "You are died",
        150,
        Game::Instance().getWindow()->getCenterX(),
        Game::Instance().getWindow()->getCenterY() - 150,
        Color::WHITE);
};

bool LoseState::enter()
{
    m_bLoaded = false;

    std::unique_ptr<Button> respawnButton = std::make_unique<Button>(
        "Respawn",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2,
        250,
        70);

    std::unique_ptr<Button> mainMenuButton = std::make_unique<Button>(
        "Main Menu",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);

    std::unique_ptr<Button> exitButton = std::make_unique<Button>(
        "Exit",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 200,
        250,
        70);

    if (Game::Instance().getDiamond() < 2) {
        respawnButton->disable();
    }
    respawnButton->onClick([this]() { m_bEnterRespawn = true; });

    mainMenuButton->onClick([this]() { m_bEnterMainMenu = true; });
    exitButton->onClick([this]() { m_bEnterExit = true; });

    m_uiObjects.push_back(std::move(respawnButton));
    m_uiObjects.push_back(std::move(mainMenuButton));
    m_uiObjects.push_back(std::move(exitButton));

    m_bLoaded = true;

    return true;
};

bool LoseState::exit()
{
    m_bPaused = true;
    InputHandler::Instance().reset();
    return true;
};

std::string LoseState::getStateID() const
{
    return s_stateID;
};
