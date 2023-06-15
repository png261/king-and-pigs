#include "WinState.hpp"

#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string WinState::kStateID_ = "WIN_STATE";

WinState::WinState()
    : is_enter_main_menu_(false)
    , is_enter_exit_(false){};

bool WinState::enter()
{
    is_loaded_ = false;
    const int width = 300;
    const int height = 70;
    const int margin_y = 100;

    auto main_menu_button = std::make_unique<Button>();
    main_menu_button->setTitle("Main Menu");
    main_menu_button->load(LoaderParams(
        Game::Instance().getWindow()->getCenter().x - width * 0.5f,
        Game::Instance().getWindow()->getCenter().y - height * 0.5f,
        width,
        height));
    main_menu_button->onClick([this]() { is_enter_main_menu_ = true; });

    auto exit_button = std::make_unique<Button>();
    exit_button->setTitle("Exit");
    exit_button->load(LoaderParams(
        Game::Instance().getWindow()->getCenter().x - width * 0.5f,
        Game::Instance().getWindow()->getCenter().y - height * 0.5f + margin_y,
        width,
        height));
    exit_button->onClick([this]() { is_enter_exit_ = true; });

    ui_objects_.push_back(std::move(main_menu_button));
    ui_objects_.push_back(std::move(exit_button));

    is_loaded_ = true;

    return true;
};

void WinState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }


    if (is_enter_main_menu_) {
        GameStateManager::Instance().clean();
        GameStateManager::Instance().changeState(std::make_unique<MainMenuState>());
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

bool WinState::exit()
{
    pause();
    InputManager::Instance().reset();
    return true;
};

std::string WinState::getStateID() const
{
    return kStateID_;
};
