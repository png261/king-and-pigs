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
    , m_pRenderer(nullptr)
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

bool Game::init(int width, int height, Uint32 flags)
{
    if (SDL::init() == false) {
        return false;
    };

    if (Box2D::Instance()->init() == false) {
        return false;
    };

    SDL_CreateWindowAndRenderer(width, height, flags, &m_pWindow, &m_pRenderer);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(m_pRenderer, width, height);

    m_gameWidth = width;
    m_gameHeight = height;
    m_levelWidth = width;
    m_levelHeight = height;
    m_bRunning = true;

    GameStateMachine::Instance()->changeState(new PlayState());
    return true;
}

void Game::handleEvents()
{
    InputHandler::Instance()->update();
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_Q)) {
        Box2D::Instance()->toggleDebugDraw();
    };
}

void Game::update()
{
    GameStateMachine::Instance()->update();
    Box2D::Instance()->update();
}

void Game::render()
{
    SDL_RenderClear(getRenderer());
    GameStateMachine::Instance()->render();
    Box2D::Instance()->debugDraw();
    SDL_RenderPresent(getRenderer());
}

void Game::clean()
{
    SDL::exit();
}

void Game::quit()
{
    m_bRunning = false;
}


SDL_Renderer* Game::getRenderer() const
{
    return m_pRenderer;
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

int Game::getGameWidth() const
{
    return m_gameWidth;
}

int Game::getGameHeight() const
{
    return m_gameHeight;
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
