#include "Game.hpp"

#include <memory>
#include "CONSTANT.hpp"
#include "GameObjectFactory.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "MainMenuState.hpp"
#include "PhysicWorld.hpp"
#include "PlayState.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"
#include "WinState.hpp"

Game::Game()
    : m_bRunning(false)
    , m_bDebug(false)
{
    m_levelFiles.push_back(LEVEL_DIRECTORY + "level1.tmx");
    m_levelFiles.push_back(LEVEL_DIRECTORY + "level2.tmx");
    m_levelFiles.push_back(LEVEL_DIRECTORY + "test.tmx");
    m_levelIndex = 0;
}

Game& Game::Instance()
{
    static Game s_instance{};
    return s_instance;
}

bool Game::init()
{
    if (!SDL::init()) {
        return false;
    };

    m_pWindow = std::make_unique<Window>(1280, 720, "King and Pig");

    if (!PhysicWorld::Instance().init(m_pWindow.get())) {
        return false;
    };

    GameStateMachine::Instance().changeState(new MainMenuState());
    m_bRunning = true;

    return true;
}

void Game::handleEvents()
{
    InputHandler::Instance().update();
}

void Game::update()
{
    GameStateMachine::Instance().update();
}

void Game::render() const
{
    m_pWindow->clear();
    GameStateMachine::Instance().render();
    m_pWindow->refresh();
    m_pWindow->delayFramerateIfNeeded();
}

void Game::clean()
{
    PhysicWorld::Instance().clean();
    GameStateMachine::Instance().clean();
    GameObjectFactory::Instance().clean();
    InputHandler::Instance().clean();
    TextureManager::Instance().clean();
    SoundManager::Instance().clean();
    SDL::exit();
}

void Game::quit()
{
    m_bRunning = false;
}

void Game::setLevel(Level* const pLevel)
{
    m_pLevel = pLevel;
}

void Game::setLevelIndex(const int index)
{
    m_levelIndex = index;
}

void Game::nextLevel()
{
    PlayState* const playState =
        dynamic_cast<PlayState*>(GameStateMachine::Instance().getCurrentState());
    if (playState == nullptr) {
        return;
    }

    m_levelIndex += 1;
    if (m_levelIndex >= m_levelFiles.size()) {
        GameStateMachine::Instance().changeState(new WinState());
        m_levelIndex = 0;
        return;
    }

    playState->loadLevel();
}

int Game::getLevelIndex() const
{
    return m_levelIndex;
}

bool Game::isRunning() const
{
    return m_bRunning;
}

std::string Game::getLevelPath(int index)
{
    return m_levelFiles[index];
}

Window* Game::getWindow() const
{
    return m_pWindow.get();
}

Level* Game::getLevel() const
{
    return m_pLevel;
}

bool Game::isDebug() const
{
    return m_bDebug;
}

void Game::toggleDebug()
{
    m_bDebug = !m_bDebug;
}
