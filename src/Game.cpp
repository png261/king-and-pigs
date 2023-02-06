#include "Game.h"

#include "InputHandler.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "SoundManager.h"
#include "TextureManager.h"

bool Game::init(const char *title, int x, int y, int width, int height, Uint32 flags) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("fail to init SDL");
        return false;
    }

    m_pWindow = SDL_CreateWindow(title, x, y, width, height, flags);
    if(m_pWindow == NULL) {
        SDL_Log("fail to create Window");
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if(m_pRenderer == NULL) {
        SDL_Log("fail to create Renderer");
        return false;
    }

    m_width = width;
    m_height = height;
    m_bRunning = true;

    TextureManager::Instance()->load("assets/01-King Human/Idle (78x58).png", "player idle", m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Run (78x58).png", "player run", m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Jump (78x58).png", "player jump", m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Attack (78x58).png", "player attack", m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Dead (78x58).png", "player dead", m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Fall (78x58).png", "player fall", m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Ground (78x58).png", "player ground", m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Hit (78x58).png", "player hit", m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Door In (78x58).png", "player doorIn", m_pRenderer);

    GameStateMachine::Instance()->pushState(new PlayState());


    return true;
}

void Game::handleEvents() {
    InputHandler::Instance()->update();
}

void Game::update() {
    GameStateMachine::Instance()->update();
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);
    GameStateMachine::Instance()->render();
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
}
