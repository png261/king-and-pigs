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
    : m_pLevel(nullptr)
    , m_bRunning(false)
{
    m_levelFiles.push_back(LEVELS_DIR + "level1.tmx");
    m_levelFiles.push_back(LEVELS_DIR + "level2.tmx");
    m_levelFiles.push_back(LEVELS_DIR + "test.tmx");
    m_levelIndex = 0;
}

std::shared_ptr<Game> Game::Instance()
{
    static std::shared_ptr<Game> s_pInstance{new Game};
    return s_pInstance;
}

bool Game::init()
{
    if (SDL::init() == false) {
        return false;
    };

    m_pWindow = std::make_shared<Window>(1280, 720);

    if (PhysicWorld::Instance()->init(m_pWindow) == false) {
        return false;
    };

    GameStateMachine::Instance()->changeState(new MainMenuState());
    m_bRunning = true;

    return true;
}

void Game::handleEvents()
{
    InputHandler::Instance()->update();
}

void Game::update()
{
    GameStateMachine::Instance()->update();
}

void Game::render()
{
    m_pWindow->clear();

    GameStateMachine::Instance()->render();
    m_pWindow->refresh();
    m_pWindow->delayFramerateIfNeeded();
}

void Game::clean()
{
    PhysicWorld::Instance()->clean();
    GameStateMachine::Instance()->clean();
    GameObjectFactory::Instance()->clean();
    InputHandler::Instance()->clean();
    TextureManager::Instance()->clean();
    SoundManager::Instance()->clean();
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

void Game::nextLevel()
{
    PlayState* playState =
        dynamic_cast<PlayState*>(GameStateMachine::Instance()->getCurrentState());
    if (playState == nullptr) {
        return;
    }

    m_levelIndex += 1;
    if (m_levelIndex >= m_levelFiles.size()) {
        GameStateMachine::Instance()->changeState(new WinState());
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

std::shared_ptr<Window> Game::getWindow()
{
    return m_pWindow;
}

Level* Game::getLevel()
{
    return m_pLevel;
}
