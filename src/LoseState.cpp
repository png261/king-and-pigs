#include "LoseState.hpp"

#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string LoseState::kStateID_ = "LOSE_STATE";

LoseState::LoseState()
    : is_enter_main_menu(false)
    , is_enter_exit_(false){};

bool LoseState::enter()
{
    is_loaded_ = false;

    auto respawn_button = std::make_unique<Button>();
    respawn_button->setTitle("Respawn");
    respawn_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - 250 * 0.5f,
        Game::Instance().getWindow()->getCenter().y - 70 * 0.5f,
        250,
        70));
    respawn_button->onClick([this]() { is_enter_respawn_ = true; });
    if (Game::Instance().getDiamond() < 2) {
        respawn_button->disable();
    }

    auto main_menu_button = std::make_unique<Button>();
    main_menu_button->setTitle("Main Menu");
    main_menu_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - 250 * 0.5f,
        Game::Instance().getWindow()->getCenter().y - 70 * 0.5f + 100,
        250,
        70));
    main_menu_button->onClick([this]() { is_enter_main_menu = true; });

    auto exit_button = std::make_unique<Button>();
    exit_button->setTitle("Exit");
    exit_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - 250 * 0.5f,
        Game::Instance().getWindow()->getCenter().y - 70 * 0.5f + 200,
        250,
        70));
    exit_button->onClick([this]() { is_enter_exit_ = true; });

    ui_objects_.push_back(std::move(respawn_button));
    ui_objects_.push_back(std::move(main_menu_button));
    ui_objects_.push_back(std::move(exit_button));

    is_loaded_ = true;

    return true;
};

void LoseState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (is_enter_respawn_) {
        Game::Instance().useDiamond(2);
        GameStateManager::Instance().changeState(std::make_unique<PlayState>());
        return;
    }

    if (is_enter_main_menu) {
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

void LoseState::render() const
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    Game::Instance().getWindow()->drawOverlay({0, 0, 0, 100});

    for (const auto& obj : ui_objects_) {
        obj->draw();
    }

    Game::Instance().getWindow()->print(
        "You are died",
        Game::Instance().getWindow()->getCenter().x,
        Game::Instance().getWindow()->getCenter().y - 150,
        150,
        ColorName::WHITE);
};


bool LoseState::exit()
{
    pause();
    InputManager::Instance().reset();
    return true;
};

std::string LoseState::getStateID() const
{
    return kStateID_;
};
