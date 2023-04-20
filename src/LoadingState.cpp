#include "LoadingState.hpp"

#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "PauseState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string LoadingState::kId_ = "LOADING";

LoadingState::LoadingState() {}

void LoadingState::update(){};

void LoadingState::render() const
{
    Game::Instance().getWindow()->print(
        "Loading...",
        100,
        Game::Instance().getWindow()->getCenterX(),
        Game::Instance().getWindow()->getCenterY(),
        Color::WHITE);
};

bool LoadingState::enter()
{
    return true;
};

bool LoadingState::exit()
{
    pause();
    InputHandler::Instance().reset();
    return true;
};

std::string LoadingState::getStateID() const
{
    return kId_;
};
