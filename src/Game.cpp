#include "Game.hpp"
#include <SDL2/SDL_render.h>

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
    : m_pWindow(NULL)
    , m_pRenderer(NULL)
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
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Log::error("fail to init SDL");
        return false;
    }

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
}

void Game::update()
{
    GameStateMachine::Instance()->update();
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    GameStateMachine::Instance()->render();
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {}

void Game::quit()
{
    m_bRunning = false;
}


SDL_Renderer* Game::getRenderer()
{
    return m_pRenderer;
}


int Game::getCurrentLevel() const
{
    return m_currentLevel;
}

void Game::setNextLevel(int nextLevel)
{
    m_nextLevel = nextLevel;
}

int Game::getNextLevel() const
{
    return m_nextLevel;
}

void Game::setLevelComplete(bool levelComplete)
{
    m_bLevelComplete = levelComplete;
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

void Game::setLevelWidth(int width)
{
    m_levelWidth = width;
}

void Game::setLevelHeight(int height)
{
    m_levelHeight = height;
}

int Game::getLevelWidth() const
{
    return m_levelWidth;
}

int Game::getLevelHeight() const
{
    return m_levelHeight;
}

Player* Game::getPlayer()
{
    return m_pPlayer;
}

void Game::setPlayer(Player* pPlayer)
{
    m_pPlayer = pPlayer;
}

std::vector<std::string> Game::getLevelFiles()
{
    return m_levelFiles;
}

void Game::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    m_bLevelComplete = false;
}
