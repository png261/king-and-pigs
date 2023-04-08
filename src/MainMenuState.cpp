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

MainMenuState::~MainMenuState()
{
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

    if (m_bEnterPlayState) {
        Game::Instance()->setLevelIndex(0);
        GameStateMachine::Instance()->changeState(std::make_shared<PlayState>());
        return;
    }

    if (m_bEnterQuit) {
        Game::Instance()->quit();
        return;
    }

    for (const auto& obj : m_uiObjects) {
        obj->update();
    }
};

void MainMenuState::render() const
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }
    for (const auto& obj : m_uiObjects) {
        obj->draw();
    }
};

bool MainMenuState::load()
{
    m_bLoaded = false;
    const auto texture = TextureManager::Instance();
    texture->load(ASSETS_DIR + "UI/Button/normal.png", "button normal");
    texture->load(ASSETS_DIR + "UI/Button/hovered.png", "button hovered");
    texture->load(ASSETS_DIR + "UI/Button/pressed.png", "button pressed");

    Button* newGameButton = new Button(
        "New Game",
        Game::Instance()->getWindow()->getCenterX() - 250 / 2,
        Game::Instance()->getWindow()->getCenterY() - 70 / 2,
        250,
        70);

    Button* exitButton = new Button(
        "Exit",
        Game::Instance()->getWindow()->getCenterX() - 250 / 2,
        Game::Instance()->getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);

    newGameButton->onClick([this]() { m_bEnterPlayState = true; });
    exitButton->onClick([this]() { m_bEnterQuit = true; });

    m_uiObjects.push_back(std::unique_ptr<UiObject>(newGameButton));
    m_uiObjects.push_back(std::unique_ptr<UiObject>(exitButton));

    m_bLoaded = true;
    return true;
};

bool MainMenuState::onExit()
{
    m_bPaused = true;
    InputHandler::Instance()->reset();
    return true;
};

std::string MainMenuState::getStateID() const
{
    return s_stateID;
};
