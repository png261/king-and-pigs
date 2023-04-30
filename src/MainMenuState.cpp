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

    TextureManager::Instance().draw(
        "logo",
        Game::Instance().getWindow()->getCenter() - b2Vec2(400, 250),
        134,
        14,
        false,
        6);

    const Json::Value& config = Utils::read_json_file(CONFIG_FILE);
    const std::string& github = config["author"]["github"].asString();
    const std::string& email = config["author"]["email"].asString();

    Game::Instance().getWindow()->print(
        github + " - " + email,
        Game::Instance().getWindow()->getCenter().x,
        Game::Instance().getWindow()->getHeight() - 50,
        20,
        ColorName::WHITE,
        ITALIC);
};

bool MainMenuState::enter()
{
    is_loaded_ = false;

    TextureManager& texture = TextureManager::Instance();
    texture.load(IMAGE_DIRECTORY + "ui/logo.png", "logo");

    auto new_game_button = std::make_unique<Button>();
    new_game_button->setTitle("New Game");
    new_game_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - 300 / 2.0f,
        Game::Instance().getWindow()->getCenter().y - 70 / 2.0f,
        300,
        70));

    auto exit_button = std::make_unique<Button>();
    exit_button->setTitle("Exit");
    exit_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - 300 / 2.0f,
        Game::Instance().getWindow()->getCenter().y - 70 / 2.0f + 100,
        300,
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
