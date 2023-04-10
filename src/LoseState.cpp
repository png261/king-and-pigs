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

LoseState::~LoseState(){};

void LoseState::update()
{
    if (!m_bLoaded || m_bPaused) {
        return;
    }

    if (m_bEnterMainMenu) {
        GameStateMachine::Instance().changeState(new MainMenuState());
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

void LoseState::s_mainMenu()
{
    GameStateMachine::Instance().changeState(new MainMenuState());
}

void LoseState::s_exit()
{
    Game::Instance().quit();
}

bool LoseState::enter()
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
