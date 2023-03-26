#include "Game.hpp"

#include <memory>
#include "CONSTANT.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "PhysicWorld.hpp"
#include "PlayState.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"

Game::Game()
    : m_pWindow(nullptr)
    , m_pLevel(nullptr)
    , m_bRunning(false)
    , m_bDebug(false)
{
    m_levelFiles.push_back(LEVELS_DIR + "level1.tmx");
    m_levelFiles.push_back(LEVELS_DIR + "level2.tmx");
    m_levelFiles.push_back(LEVELS_DIR + "test.tmx");
    m_currentLevel = 0;
}

Game::~Game() {}

Game* Game::Instance()
{
    static Game* const s_pInstance = new Game();
    return s_pInstance;
}

bool Game::init()
{
    if (SDL::init() == false) {
        return false;
    };

    m_pWindow = new Window(700, 400);

    if (PhysicWorld::Instance()->init(m_pWindow) == false) {
        return false;
    };

    GameStateMachine::Instance()->changeState(new PlayState());
    m_bRunning = true;

    return true;
}

void Game::handleEvents()
{
    InputHandler::Instance()->update();
    if (InputHandler::Instance()->isKeyDown(KEY_Q)) {
        m_bDebug = !m_bDebug;
    };

    PhysicWorld::Instance()->handleEvents();
}

void Game::update()
{
    PhysicWorld::Instance()->update();
    GameStateMachine::Instance()->update();
}

void Game::render()
{
    m_pWindow->clear();

    GameStateMachine::Instance()->render();
    if (m_bDebug) {
        PhysicWorld::Instance()->debugDraw();
    }

    m_pWindow->refresh();
    m_pWindow->delayFramerateIfNeeded();
}

void Game::clean()
{
    PhysicWorld::Instance()->clean();
    GameStateMachine::Instance()->clean();
    InputHandler::Instance()->clean();
    TextureManager::Instance()->clean();
    SoundManager::Instance()->clean();
    SDL::exit();
}

void Game::quit()
{
    m_bRunning = false;
}

void Game::setLevel(Level* pLevel)
{
    m_pLevel = pLevel;
}

void Game::nextLevel()
{
    m_currentLevel += 1;
    if (m_currentLevel >= m_levelFiles.size()) {
        /* TODO: win screen */
        return;
    }

    GameStateMachine::Instance()->changeState(new PlayState());
}

int Game::getCurrentLevel() const
{
    return m_currentLevel;
}

bool Game::isRunning() const
{
    return m_bRunning;
}


std::string Game::loadLevel(int index)
{
    return m_levelFiles[index];
}

Window* Game::getWindow()
{
    return m_pWindow;
}

Level* Game::getLevel()
{
    return m_pLevel;
}

bool Game::isDebug() const
{
    return m_bDebug;
}
