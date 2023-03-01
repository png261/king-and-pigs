#include "Game.hpp"

#include "Box2D.hpp"
#include "Camera.hpp"
#include "GameObjectFactory.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "MainMenuState.hpp"
#include "MenuButton.hpp"
#include "PlayState.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"

Game::Game()
    : m_pWindow(nullptr)
    , m_bRunning(false)
    , m_bLevelComplete(false)
{
    m_levelFiles.push_back("levels/level1.tmx");
    m_levelFiles.push_back("levels/level2.tmx");
    m_currentLevel = 1;
}

Game* Game::Instance()
{
    static Game* s_pInstance = new Game();
    return s_pInstance;
}

bool Game::init(unsigned int width, unsigned int height)
{
    if (SDL::init() == false) {
        return false;
    };

    if (Box2D::Instance()->init() == false) {
        return false;
    };

    m_pWindow = new Window(width, height, "");

    m_levelWidth = width;
    m_levelHeight = height;
    m_bRunning = true;

    GameStateMachine::Instance()->changeState(new PlayState());
    return true;
}

void Game::handleEvents()
{
    InputHandler::Instance()->update();
    Box2D::Instance()->handleEvents();
}

void Game::update()
{
    GameStateMachine::Instance()->update();
    Box2D::Instance()->update();
}

void Game::render()
{
    m_pWindow->clear();

    GameStateMachine::Instance()->render();
    Box2D::Instance()->debugDraw();

    m_pWindow->refresh();
    m_pWindow->delayFramerateIfNeeded();
}

void Game::clean()
{
    Box2D::Instance()->clean();
    delete m_pWindow;
    SDL::exit();
}

void Game::quit()
{
    m_bRunning = false;
}

int Game::getCurrentLevel() const
{
    return m_currentLevel;
}

int Game::getNextLevel() const
{
    return m_nextLevel;
}

bool Game::isLevelComplete() const
{
    return m_bLevelComplete;
}

bool Game::isRunning() const
{
    return m_bRunning;
}

int Game::getLevelWidth() const
{
    return m_levelWidth;
}

int Game::getLevelHeight() const
{
    return m_levelHeight;
}

Player* Game::getPlayer() const
{
    return m_pPlayer;
}

std::vector<std::string> Game::getLevelFiles()
{
    return m_levelFiles;
}

void Game::setLevelComplete(bool levelComplete)
{
    m_bLevelComplete = levelComplete;
}

void Game::setNextLevel(int nextLevel)
{
    m_nextLevel = nextLevel;
}


void Game::setLevelWidth(int width)
{
    m_levelWidth = width;
}

void Game::setLevelHeight(int height)
{
    m_levelHeight = height;
}


void Game::setPlayer(Player* pPlayer)
{
    m_pPlayer = pPlayer;
}

void Game::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    m_bLevelComplete = false;
}

Window* Game::getWindow()
{
    return m_pWindow;
}
