#include "Game.hpp"

#include <memory>

#include "CONSTANT.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "Log.hpp"
#include "MainMenuState.hpp"
#include "ObjectFactory.hpp"
#include "PhysicManager.hpp"
#include "PlayState.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"
#include "WinState.hpp"

Game::Game()
    : is_running_(false)
    , is_debug_(false)
    , level_index_(0)
    , top_score_(0)
    , score_(0)
{}

Game& Game::Instance()
{
    static Game instance{};
    return instance;
}

void Game::init(const int width, const int height, const std::string& title)
{
    SDL::init();
    window_ = std::make_unique<Window>(width, height, title);
    PhysicManager::Instance().init(window_.get());

    cursor_ = std::make_unique<Cursor>();
    cursor_->init();

    level_files_.push_back(LEVEL_DIRECTORY + "level1.json");
    level_files_.push_back(LEVEL_DIRECTORY + "level2.json");
    GameStateManager::Instance().changeState(std::make_unique<MainMenuState>());

    is_running_ = true;
}

void Game::handleEvents()
{
    InputManager::Instance().update();
}

void Game::update()
{
    cursor_->reset();
    GameStateManager::Instance().update();
}

void Game::render() const
{
    window_->clear();

    GameStateManager::Instance().render();
    cursor_->draw();

    window_->refresh();
}

void Game::handleFPS() const
{
    window_->delayFramerateIfNeeded();
}

void Game::clean()
{
    ObjectFactory::Instance().clean();
    PhysicManager::Instance().clean();
    GameStateManager::Instance().clean();
    InputManager::Instance().clean();
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
        dynamic_cast<PlayState*>(GameStateManager::Instance().getCurrentState());
    if (play_state == nullptr) {
        return;
    }

    level_index_ += 1;
    if (level_index_ >= level_files_.size()) {
        handleWin();
        return;
    }

    GameStateManager::Instance().loading();
    play_state->loadLevel();
}

void Game::handleWin()
{
    GameStateManager::Instance().pushState(std::make_unique<WinState>());
    level_index_ = 0;
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

void Game::debugMode(const bool is_debug)
{
    is_debug_ = is_debug;
    if (isDebug()) {
        Log::log(">Debug mode activated");
    }
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

int Game::getTopScore() const
{
    return top_score_;
}

void Game::addScore(const int score)
{
    score_ += score;
    top_score_ = std::max(top_score_, score_);
}
