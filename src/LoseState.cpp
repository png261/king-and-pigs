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
    : is_enter_respawn_(false)
    , is_enter_new_game_(false)
    , is_enter_main_menu_(false)
{}

bool LoseState::enter()
{
    is_loaded_ = false;

    auto respawn_button = std::make_unique<Button>();
    respawn_button->setTitle("Respawn (2 diamond)");
    respawn_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - 340 * 0.5f,
        Game::Instance().getWindow()->getCenter().y - 70 * 0.5f,
        340,
        70));
    respawn_button->onClick([this]() { is_enter_respawn_ = true; });
    if (Game::Instance().getDiamond() < 2) {
        respawn_button->disable();
    }
    const int button_width = 300;
    const int button_height = 70;
    const int margin_y = 100;

    auto new_game_button = std::make_unique<Button>();
    new_game_button->setTitle("New Game");
    new_game_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - button_width * 0.5f,
        Game::Instance().getWindow()->getCenter().y - button_height * 0.5f + margin_y,
        button_width,
        button_height));
    new_game_button->onClick([this]() { is_enter_new_game_ = true; });

    auto main_menu_button = std::make_unique<Button>();
    main_menu_button->setTitle("Main Menu");
    main_menu_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - button_width * 0.5f,
        Game::Instance().getWindow()->getCenter().y - button_height * 0.5f + margin_y * 2,
        button_width,
        button_height));
    main_menu_button->onClick([this]() { is_enter_main_menu_ = true; });

    ui_objects_.push_back(std::move(respawn_button));
    ui_objects_.push_back(std::move(new_game_button));
    ui_objects_.push_back(std::move(main_menu_button));

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

    if (is_enter_new_game_) {
        Game::Instance().setLevelIndex(0);
        GameStateManager::Instance().changeState(std::make_unique<PlayState>());
        return;
    }

    if (is_enter_main_menu_) {
        GameStateManager::Instance().clean();
        GameStateManager::Instance().changeState(std::make_unique<MainMenuState>());
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
