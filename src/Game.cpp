#include "Game.h"
#include <iostream>

#include "GameObjectFactory.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "SoundManager.h"
#include "TextureManager.h"

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

void Game::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    m_bLevelComplete = false;
}

bool Game::init(const char* title, int x, int y, int width, int height, Uint32 flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("fail to init SDL");
        return false;
    }

    m_pWindow = SDL_CreateWindow(title, x, y, width, height, flags);
    if (m_pWindow == NULL) {
        SDL_Log("fail to create Window");
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if (m_pRenderer == NULL) {
        SDL_Log("fail to create Renderer");
        return false;
    }

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
