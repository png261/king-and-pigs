#include "Game.h"

#include "InputHandler.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "SoundManager.h"
#include "TextureManager.h"

bool Game::init(const char *title, int x, int y, int w, int h, Uint32 flags) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("fail to init SDL");
        return false;
    }

    m_pWindow = SDL_CreateWindow(title, x, y, w, h, flags);
    if(m_pWindow == NULL) {
        SDL_Log("fail to create Window");
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if(m_pRenderer == NULL) {
        SDL_Log("fail to create Renderer");
        return false;
    }

    m_bRunning = true;

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
