#include "Game.h"

#include "GameStateMachine.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "SoundManager.h"
#include "TextureManager.h"

bool Game::init(const char *title, int x, int y, int width, int height,
                Uint32 flags) {
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

    m_width = width;
    m_height = height;
    m_bRunning = true;

    TextureManager::Instance()->load("assets/01-King Human/Idle (78x58).png",
                                     "player idle", 11, m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Run (78x58).png",
                                     "player run", 8, m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Jump (78x58).png",
                                     "player jump", 1, m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Attack (78x58).png",
                                     "player attack", 3, m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Dead (78x58).png",
                                     "player dead", 4, m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Fall (78x58).png",
                                     "player fall", 1, m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Ground (78x58).png",
                                     "player ground", 1, m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Hit (78x58).png",
                                     "player hit", 2, m_pRenderer);
    TextureManager::Instance()->load("assets/01-King Human/Door In (78x58).png",
                                     "player doorIn", 8, m_pRenderer);
    TextureManager::Instance()->load(
        "assets/01-King Human/Door Out (78x58).png", "player doorOut", 8,
        m_pRenderer);

    TextureManager::Instance()->load("assets/03-Pig/Idle (34x28).png",
                                     "enemy_pig idle", 11, m_pRenderer);
    TextureManager::Instance()->load("assets/03-Pig/Run (34x28).png",
                                     "enemy_pig run", 6, m_pRenderer);
    TextureManager::Instance()->load("assets/03-Pig/Jump (34x28).png",
                                     "enemy_pig jump", 1, m_pRenderer);
    TextureManager::Instance()->load("assets/03-Pig/Attack (34x28).png",
                                     "enemy_pig attack", 3, m_pRenderer);
    TextureManager::Instance()->load("assets/03-Pig/Dead (34x28).png",
                                     "enemy_pig dead", 4, m_pRenderer);
    TextureManager::Instance()->load("assets/03-Pig/Fall (34x28).png",
                                     "enemy_pig fall", 1, m_pRenderer);
    TextureManager::Instance()->load("assets/03-Pig/Ground (34x28).png",
                                     "enemy_pig ground", 1, m_pRenderer);
    TextureManager::Instance()->load("assets/03-Pig/Hit (34x28).png",
                                     "enemy_pig hit", 2, m_pRenderer);

    GameStateMachine::Instance()->pushState(new PlayState());

    return true;
}

void Game::handleEvents() { InputHandler::Instance()->update(); }

void Game::update() { GameStateMachine::Instance()->update(); }

void Game::render() {
    SDL_RenderClear(m_pRenderer);
    GameStateMachine::Instance()->render();
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {}
