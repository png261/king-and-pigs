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

const std::string MainMenuState::kId_ = "MAIN_MENU";

MainMenuState::MainMenuState()
    : is_enterPlayState_(false)
    , is_enterQuit_(false){};

void MainMenuState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (is_enterPlayState_) {
        Game::Instance().setLevelIndex(0);
        GameStateMachine::Instance().loading();
        GameStateMachine::Instance().changeState(std::make_unique<PlayState>());
        return;
    }

    if (is_enterQuit_) {
        Game::Instance().quit();
        return;
    }

    for (const auto& obj : ui_objects_) {
        obj->update();
    }
};

void MainMenuState::render() const
{
    if (!isLoaded() || isPaused()) {
        return;
    }
    for (const auto& obj : ui_objects_) {
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
    is_loaded_ = false;

    std::unique_ptr<Button> newGameButton = std::make_unique<Button>(
        "New Game",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2,
        250,
        70);

    std::unique_ptr<Button> exit_button = std::make_unique<Button>(
        "Exit",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);

    newGameButton->onClick([this]() { is_enterPlayState_ = true; });
    exit_button->onClick([this]() { is_enterQuit_ = true; });

    ui_objects_.push_back(std::move(newGameButton));
    ui_objects_.push_back(std::move(exit_button));

    is_loaded_ = true;
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
    return kId_;
};
