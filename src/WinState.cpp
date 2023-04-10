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

WinState::~WinState(){};

void WinState::update()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }


    if (m_bEnterMainMenu) {
        GameStateMachine::Instance().changeState(std::make_shared<MainMenuState>());
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
    if (!m_bLoaded || m_bPaused) {
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
    TextureManager& texture = TextureManager::Instance();
    texture.load(IMAGE_DIRECTORY + "UI/Button/normal.png", "button normal");
    texture.load(IMAGE_DIRECTORY + "UI/Button/hovered.png", "button hovered");
    texture.load(IMAGE_DIRECTORY + "UI/Button/pressed.png", "button pressed");

    Button* mainMenuButton = new Button(
        "Main Menu",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2,
        250,
        70);

    Button* exitButton = new Button(
        "Exit",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);

    mainMenuButton->onClick([this]() { m_bEnterMainMenu = true; });
    exitButton->onClick([this]() { m_bEnterExit = true; });

    m_uiObjects.push_back(std::unique_ptr<UiObject>(mainMenuButton));
    m_uiObjects.push_back(std::unique_ptr<UiObject>(exitButton));

    m_bLoaded = true;

    return true;
};

bool WinState::exit()
{
    m_bPaused = true;
    InputHandler::Instance().reset();
    return true;
};

std::string WinState::getStateID() const
{
    return s_stateID;
};
