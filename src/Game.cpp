#include "Game.hpp"

#include <memory>

#include "CONSTANT.hpp"
#include "ObjectFactory.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "LoadingState.hpp"
#include "MainMenuState.hpp"
#include "PhysicWorld.hpp"
#include "PlayState.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"
#include "WinState.hpp"

Game::Game()
    : is_running_(false)
    , is_debug_(false)
    , level_index_(0)
    , score_(0)
    , highest_score_(0)
{}

Game& Game::Instance()
{
    static Game instance{};
    return instance;
}

void Game::init()
{
    SDL::init();
    window_ = std::make_unique<Window>(1280, 720, "King and Pig");
    PhysicWorld::Instance().init(window_.get());

    cursor_ = std::make_unique<Cursor>();
    cursor_->init();

    level_files_.push_back(LEVEL_DIRECTORY + "level1.json");
    level_files_.push_back(LEVEL_DIRECTORY + "level2.json");
    GameStateMachine::Instance().changeState(std::make_unique<MainMenuState>());

    is_running_ = true;
}

void Game::handleEvents()
{
    InputHandler::Instance().update();
}

void Game::update()
{
    cursor_->resetState();
    GameStateMachine::Instance().update();
}

void Game::render() const
{
    window_->clear();

    GameStateMachine::Instance().render();
    cursor_->draw();

    window_->refresh();
}

void Game::handleFPS() const
{
    window_->delayFramerateIfNeeded();
}

void Game::clean()
{
    PhysicWorld::Instance().clean();
    GameStateMachine::Instance().clean();
    ObjectFactory::Instance().clean();
    InputHandler::Instance().clean();
    TextureManager::Instance().clean();
    SoundManager::Instance().clean();
    SDL::exit();
}

void Game::quit()
{
    is_running_ = false;
}

void Game::setLevel(Level* const level)
{
    level_ = level;
}

void Game::setLevelIndex(const int level_index)
{
    level_index_ = level_index;
}

void Game::nextLevel()
{
    auto const play_state =
        dynamic_cast<PlayState*>(GameStateMachine::Instance().getCurrentState());
    if (play_state == nullptr) {
        return;
    }

    level_index_ += 1;
    if (level_index_ >= level_files_.size()) {
        GameStateMachine::Instance().pushState(std::make_unique<WinState>());
        level_index_ = 0;
        return;
    }

    GameStateMachine::Instance().loading();
    play_state->loadLevel();
}

int Game::getLevelIndex() const
{
    return level_index_;
}

bool Game::isRunning() const
{
    return is_running_;
}

std::string Game::getLevelPath(int level_index)
{
    return level_files_[level_index];
}

Window* Game::getWindow() const
{
    return window_.get();
}

Level* Game::getLevel() const
{
    return level_;
}

bool Game::isDebug() const
{
    return is_debug_;
}

void Game::toggleDebug()
{
    is_debug_ = !is_debug_;
}

void Game::addDiamond(int n)
{
    num_diamond_ += n;
}

int Game::getDiamond() const
{
    return num_diamond_;
}

void Game::useDiamond(int n)
{
    num_diamond_ -= n;
}

Cursor* Game::getCursor()
{
    return cursor_.get();
}

int Game::getScore() const
{
    return score_;
}

void Game::resetScore()
{
    score_ = 0;
}

int Game::getHighestScore() const
{
    return highest_score_;
}

void Game::addScore(const int score)
{
    score_ += score;
    highest_score_ = std::max(highest_score_, score_);
}
