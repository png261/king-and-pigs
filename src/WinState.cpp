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

    Game::Instance().getWindow()->drawOverlay({0, 0, 0, 100});
    for (const auto& obj : ui_objects_) {
        obj->draw();
    }
    Game::Instance().getWindow()->print(
        "You are win",
        Game::Instance().getWindow()->getCenter().x,
        Game::Instance().getWindow()->getCenter().y - 150,
        150,
        ColorName::WHITE);
};

bool WinState::enter()
{
    is_loaded_ = false;

    auto main_menu_button = std::make_unique<Button>();
    main_menu_button->setTitle("Main Menu");
    main_menu_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - 250 * 0.5f,
        Game::Instance().getWindow()->getCenter().y - 70 * 0.5f,
        250,
        70));

    auto exit_button = std::make_unique<Button>();
    exit_button->setTitle("Exit");
    exit_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - 250 * 0.5f,
        Game::Instance().getWindow()->getCenter().y - 70 * 0.5f + 100,
        250,
        70));

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
