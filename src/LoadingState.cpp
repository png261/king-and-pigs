#include "LoadingState.hpp"

#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "Log.hpp"
#include "PauseState.hpp"
#include "PlayState.hpp"
#include "TextureManager.hpp"

const std::string LoadingState::kId_ = "LOADING";

LoadingState::LoadingState() {}

void LoadingState::update(){};

void LoadingState::render() const
{
    Game::Instance().getWindow()->drawOverlay({0, 0, 0, 100});
    Game::Instance().getWindow()->print(
        "Loading...",
        Game::Instance().getWindow()->getCenter().x,
        Game::Instance().getWindow()->getCenter().y,
        100,
        ColorName::WHITE);
};

bool LoadingState::enter()
{
    return true;
};

bool LoadingState::exit()
{
    pause();
    InputManager::Instance().reset();
    return true;
};

std::string LoadingState::getStateID() const
{
    return kId_;
};
