#include "MainMenuState.hpp"

#include <memory>

#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "HowToPlayState.hpp"
#include "InputManager.hpp"
#include "Log.hpp"
#include "PauseState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"
#include "Utils.hpp"
#include "Window.hpp"

const std::string MainMenuState::kStateID_ = "MAIN_MENU_STATE";

MainMenuState::MainMenuState()
    : is_enter_play_state(false)
    , is_enter_how_to_play_state(false){};

bool MainMenuState::enter()
{
    is_loaded_ = false;

    auto& texture = TextureManager::Instance();
    texture.load(IMAGE_DIRECTORY + "ui/logo.png", "logo");

    const int button_width = 300;
    const int button_height = 70;
    const int margin_y = 100;

    auto new_game_button = std::make_unique<Button>();
    new_game_button->setTitle("New Game");
    new_game_button->load(LoaderParams(
        Game::Instance().getWindow()->getCenter().x - button_width * 0.5f,
        Game::Instance().getWindow()->getCenter().y - button_height * 0.5f,
        button_width,
        button_height));
    new_game_button->onClick([this]() { is_enter_play_state = true; });

    auto how_to_play_button = std::make_unique<Button>();
    how_to_play_button->setTitle("How To Play");
    how_to_play_button->load(LoaderParams(
        Game::Instance().getWindow()->getCenter().x - button_width * 0.5f,
        Game::Instance().getWindow()->getCenter().y - button_height * 0.5f + margin_y,
        button_width,
        button_height));
    how_to_play_button->onClick([this]() { is_enter_how_to_play_state = true; });

    ui_objects_.push_back(std::move(new_game_button));
    ui_objects_.push_back(std::move(how_to_play_button));

    is_loaded_ = true;
    return true;
};

void MainMenuState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (is_enter_play_state) {
        Game::Instance().setLevelIndex(0);
        GameStateManager::Instance().loading();
        GameStateManager::Instance().changeState(std::make_unique<PlayState>());
        return;
    }

    if (is_enter_how_to_play_state) {
        GameStateManager::Instance().pushState(std::make_unique<HowToPlayState>());
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

    Game::Instance().getWindow()->fill(Utils::hexToRgba("#3f3851"));

    for (const auto& obj : ui_objects_) {
        obj->draw();
    }

    TextureManager::Instance().draw(
        "logo",
        Game::Instance().getWindow()->getCenter() - b2Vec2(400, 250),
        134,
        14,
        false,
        6);

    const auto& config = Game::Instance().getConfig();
    const std::string& github = config["author"]["github"].get<std::string>();
    const std::string& email = config["author"]["email"].get<std::string>();

    Game::Instance().getWindow()->print(
        github + " - " + email,
        Game::Instance().getWindow()->getCenter().x,
        Game::Instance().getWindow()->getHeight() - 50,
        20,
        ColorName::WHITE,
        FontStyle::ITALIC);
};

bool MainMenuState::exit()
{
    pause();
    InputManager::Instance().reset();
    return true;
};

std::string MainMenuState::getStateID() const
{
    return kStateID_;
};
