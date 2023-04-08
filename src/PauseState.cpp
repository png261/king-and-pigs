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

PauseState::~PauseState()
{
    Log::log("PauseState deleted");
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

    if (m_bEnterResume) {
        GameStateMachine::Instance()->popState();
        return;
    }
    if (m_bEnterMainMenu) {
        GameStateMachine::Instance()->popState();
        GameStateMachine::Instance()->changeState(std::make_shared<MainMenuState>());
        return;
    }

    if (InputHandler::Instance()->isKeyDown(KEY_ESCAPE)) {
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

bool PauseState::load()
{
    m_bLoaded = false;
    const auto texture = TextureManager::Instance();
    texture->load(ASSETS_DIR + "UI/Button/normal.png", "button normal");
    texture->load(ASSETS_DIR + "UI/Button/hovered.png", "button hovered");
    texture->load(ASSETS_DIR + "UI/Button/pressed.png", "button pressed");

    Button* resumeButton = new Button(
        "Resume",
        Game::Instance()->getWindow()->getCenterX() - 250 / 2,
        Game::Instance()->getWindow()->getCenterY() - 70 / 2,
        250,
        70);

    Button* mainMenuButton = new Button(
        "Main Menu",
        Game::Instance()->getWindow()->getCenterX() - 250 / 2,
        Game::Instance()->getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);

    resumeButton->onClick([this]() { m_bEnterResume = true; });
    mainMenuButton->onClick([this]() { m_bEnterMainMenu = true; });

    m_uiObjects.push_back(std::unique_ptr<UiObject>(resumeButton));
    m_uiObjects.push_back(std::unique_ptr<UiObject>(mainMenuButton));

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
