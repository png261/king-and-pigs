#include "WinState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string WinState::kId_ = "WIN";

WinState::WinState()
    : is_enter_main_menu_(false)
    , is_enter_exit_(false){};

void WinState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }


    if (is_enter_main_menu_) {
        GameStateMachine::Instance().clean();
        GameStateMachine::Instance().changeState(std::make_unique<MainMenuState>());
        return;
    }

    if (is_enter_exit_) {
        Game::Instance().quit();
        return;
    }

    for (const auto& obj : ui_objects_) {
        obj->update();
    }
};

void WinState::render() const
{
    if (!isLoaded() || isPaused()) {
        return;
    }
    for (const auto& obj : ui_objects_) {
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
    is_loaded_ = false;

    std::unique_ptr<Button> main_menu_button = std::make_unique<Button>(
        "Main Menu",
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

    main_menu_button->onClick([this]() { is_enter_main_menu_ = true; });
    exit_button->onClick([this]() { is_enter_exit_ = true; });

    ui_objects_.push_back(std::move(main_menu_button));
    ui_objects_.push_back(std::move(exit_button));

    is_loaded_ = true;

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
    return kId_;
};
