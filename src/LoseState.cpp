#include "LoseState.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string LoseState::kId_ = "LOSE";

LoseState::LoseState()
    : is_enter_main_menu(false)
    , is_enter_exit_(false){};

void LoseState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (is_enter_respawn_) {
        Game::Instance().useDiamond(2);
        GameStateMachine::Instance().changeState(std::make_unique<PlayState>());
        return;
    }

    if (is_enter_main_menu) {
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

void LoseState::render() const
{
    if (!isLoaded() || isPaused()) {
        return;
    }
    for (const auto& obj : ui_objects_) {
        obj->draw();
    }

    Game::Instance().getWindow()->print(
        "You are died",
        150,
        Game::Instance().getWindow()->getCenterX(),
        Game::Instance().getWindow()->getCenterY() - 150,
        Color::WHITE);
};

bool LoseState::enter()
{
    is_loaded_ = false;

    std::unique_ptr<Button> respwan_button = std::make_unique<Button>(
        "Respawn",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2,
        250,
        70);

    std::unique_ptr<Button> main_menu_button = std::make_unique<Button>(
        "Main Menu",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);

    std::unique_ptr<Button> exit_button = std::make_unique<Button>(
        "Exit",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 200,
        250,
        70);

    if (Game::Instance().getDiamond() < 2) {
        respwan_button->disable();
    }
    respwan_button->onClick([this]() { is_enter_respawn_ = true; });

    main_menu_button->onClick([this]() { is_enter_main_menu = true; });
    exit_button->onClick([this]() { is_enter_exit_ = true; });

    ui_objects_.push_back(std::move(respwan_button));
    ui_objects_.push_back(std::move(main_menu_button));
    ui_objects_.push_back(std::move(exit_button));

    is_loaded_ = true;

    return true;
};

bool LoseState::exit()
{
    pause();
    InputHandler::Instance().reset();
    return true;
};

std::string LoseState::getStateID() const
{
    return kId_;
};
