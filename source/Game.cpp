#include "Game.hpp"

#include "CONSTANT.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "Log.hpp"
#include "LoseState.hpp"
#include "MainMenuState.hpp"
#include "ObjectFactory.hpp"
#include "PhysicManager.hpp"
#include "PlayState.hpp"
#include "SDL.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"
#include "Utils.hpp"
#include "WinState.hpp"

Game::Game()
    : level_(nullptr)
    , num_diamond_(0)
    , is_running_(false)
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

void Game::readConfig()
{
    config_ = Utils::read_json_file(CONFIG_FILE);
}

void Game::init()
{
    readConfig();
    SDL::init();
    createWindow();
    PhysicManager::Instance().init(getWindow());
    createCursor();
    loadLevel();
    GameStateManager::Instance().changeState(std::make_unique<MainMenuState>());
    is_running_ = true;
}

void Game::createWindow()
{
    const auto& width = config_["width"].get<int>();
    const auto& height = config_["height"].get<int>();
    const auto& title = config_["title"].get<std::string>();

    window_ = std::make_unique<Window>(width, height, title);
    getWindow()->init();
    getWindow()->setIcon(ICON_DIRECTORY + "icon.png");
}

void Game::createCursor()
{
    cursor_ = std::make_unique<Cursor>();
    getCursor()->init();
}

void Game::loadLevel()
{
    level_files_ = config_["levels"].get<std::vector<std::string>>();
}

void Game::handleEvents()
{
    InputManager::Instance().refresh();
    while (SDL_PollEvent(&event_)) {
        if (event_.type == SDL_QUIT) {
            quit();
        }

        InputManager::Instance().update(event_);
        getWindow()->handleEvents(event_);
    }
}

void Game::update()
{
    getCursor()->reset();
    GameStateManager::Instance().update();
}

void Game::render() const
{
    getWindow()->clear();

    GameStateManager::Instance().render();
    getCursor()->draw();

    getWindow()->refresh();
}

void Game::handleFPS() const
{
    getWindow()->delayFramerateIfNeeded();
}

void Game::clean()
{
    ObjectFactory::Instance().clean();
    PhysicManager::Instance().clean();
    GameStateManager::Instance().clean();
    InputManager::Instance().clean();
    TextureManager::Instance().clean();
    SoundManager::Instance().clean();
    SDL::quit();
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
    GameState* const current_state = GameStateManager::Instance().getCurrentState();
    if (current_state->getStateID() != "PLAY_STATE") {
        return;
    }

    if (isLastLevel()) {
        handleWin();
        return;
    }

    level_index_ += 1;
    GameStateManager::Instance().loading();
    dynamic_cast<PlayState*>(current_state)->loadLevel();
}

bool Game::isLastLevel() const
{
    return level_index_ == level_files_.size() - 1;
}

void Game::resetLevel()
{
    setLevelIndex(0);
}

void Game::handleWin()
{
    GameStateManager::Instance().pushState(std::make_unique<WinState>());
    resetLevel();
}

void Game::handleLose()
{
    GameStateManager::Instance().pushState(std::make_unique<LoseState>());
}

int Game::getLevelIndex() const
{
    return level_index_;
}

bool Game::isRunning() const
{
    return is_running_;
}

std::string Game::getLevelPath(int level_index) const
{
    return level_files_.at(level_index);
}

std::string Game::getCurrentLevelPath() const
{
    return level_files_.at(getLevelIndex());
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

void Game::addDiamond(const int n)
{
    num_diamond_ += n;
}

int Game::getDiamond() const
{
    return num_diamond_;
}

void Game::useDiamond(const int n)
{
    num_diamond_ -= n;
}

Cursor* Game::getCursor() const
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

nlohmann::json Game::getConfig() const
{
    return config_;
}
