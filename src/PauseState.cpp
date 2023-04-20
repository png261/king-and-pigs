#include "PauseState.hpp"

#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string PauseState::kId_ = "PAUSE";

PauseState::PauseState()
    : is_enterResume_(false)
    , is_enter_main_menu(false){};

void PauseState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (is_enterResume_) {
        GameStateMachine::Instance().popState();
        return;
    }
    if (is_enter_main_menu) {
        GameStateMachine::Instance().popState();
        GameStateMachine::Instance().changeState(std::make_unique<MainMenuState>());
        return;
    }

    if (InputHandler::Instance().isKeyDown(KEY_ESCAPE)) {
        is_enterResume_ = true;
    }

    for (const auto& obj : ui_objects_) {
        obj->update();
    }
};

void PauseState::render() const
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    for (const auto& obj : ui_objects_) {
        obj->draw();
    }
};

bool PauseState::enter()
{
    is_loaded_ = false;

    auto resume_button = std::make_unique<Button>(
        "Resume",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2,
        250,
        70);

    auto main_menu_button = std::make_unique<Button>(
        "Main Menu",
        Game::Instance().getWindow()->getCenterX() - 250 / 2,
        Game::Instance().getWindow()->getCenterY() - 70 / 2 + 100,
        250,
        70);

    resume_button->onClick([this]() { is_enterResume_ = true; });
    main_menu_button->onClick([this]() { is_enter_main_menu = true; });

    ui_objects_.push_back(std::move(resume_button));
    ui_objects_.push_back(std::move(main_menu_button));

    is_loaded_ = true;
    return true;
};

bool PauseState::exit()
{
    pause();
    InputHandler::Instance().reset();
    return true;
};

std::string PauseState::getStateID() const
{
    return kId_;
};
