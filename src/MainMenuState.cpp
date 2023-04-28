#include "MainMenuState.hpp"

#include <memory>

#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "PauseState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"
#include "Utils.hpp"
#include "Window.hpp"

const std::string MainMenuState::kId_ = "MAIN_MENU";

MainMenuState::MainMenuState()
    : is_enter_play_state(false)
    , is_enter_quit_(false){};

void MainMenuState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (is_enter_play_state) {
        Game::Instance().setLevelIndex(0);
        GameStateMachine::Instance().loading();
        GameStateMachine::Instance().changeState(std::make_unique<PlayState>());
        return;
    }

    if (is_enter_quit_) {
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
        Game::Instance().getWindow()->getCenterX(),
        Game::Instance().getWindow()->getCenterY() - 150,
        150,
        Color::WHITE);

    Game::Instance().getWindow()->print(
        "github@png261 - nhphuong.code@gmail.com",
        Game::Instance().getWindow()->getCenterX(),
        Game::Instance().getWindow()->getHeight() - 50,
        20,
        Color::WHITE,
        ITALIC);
};

bool MainMenuState::enter()
{
    is_loaded_ = false;

    auto new_game_button = std::make_unique<Button>("New Game");
    new_game_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2,
        250,
        70));

    auto exit_button = std::make_unique<Button>("Exit");
    exit_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70));

    new_game_button->onClick([this]() { is_enter_play_state = true; });
    exit_button->onClick([this]() { is_enter_quit_ = true; });

    ui_objects_.push_back(std::move(new_game_button));
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
