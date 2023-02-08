#include "Game.h"

#include "Camera.h"
#include "GameObjectFactory.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "Pig.h"
#include "PlayState.h"
#include "Player.h"
#include "SoundManager.h"
#include "TextureManager.h"

Game::Game()
    : m_pWindow(NULL), m_pRenderer(NULL), m_bRunning(false), m_playerLives(3),
      m_bLevelComplete(false) {

    m_levelFiles.push_back("levels/level1.tmx");
    m_currentLevel = 1;
}

void Game::setCurrentLevel(int currentLevel) {
    m_currentLevel = currentLevel;
    m_bLevelComplete = false;
}

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

    m_gameWidth = width;
    m_gameHeight = height;
    m_levelWidth = width;
    m_levelHeight = height;
    m_bRunning = true;

    TextureManager::Instance()->load("assets/01-King Human/Idle (78x58).png",
                                     "player idle", m_pRenderer, 11);
    TextureManager::Instance()->load("assets/01-King Human/Run (78x58).png",
                                     "player run", m_pRenderer, 8);
    TextureManager::Instance()->load("assets/01-King Human/Jump (78x58).png",
                                     "player jump", m_pRenderer, 1);
    TextureManager::Instance()->load("assets/01-King Human/Attack (78x58).png",
                                     "player attack", m_pRenderer, 3);
    TextureManager::Instance()->load("assets/01-King Human/Dead (78x58).png",
                                     "player dead", m_pRenderer, 4);
    TextureManager::Instance()->load("assets/01-King Human/Fall (78x58).png",
                                     "player fall", m_pRenderer, 1);
    TextureManager::Instance()->load("assets/01-King Human/Ground (78x58).png",
                                     "player ground", m_pRenderer, 1);
    TextureManager::Instance()->load("assets/01-King Human/Hit (78x58).png",
                                     "player hit", m_pRenderer, 2);
    TextureManager::Instance()->load("assets/01-King Human/Door In (78x58).png",
                                     "player doorIn", m_pRenderer, 8);
    TextureManager::Instance()->load("assets/01-King Human/Door In (78x58).png",
                                     "player doorIn", m_pRenderer, 8);
    TextureManager::Instance()->load(
        "assets/01-King Human/Door Out (78x58).png", "player doorOut",
        m_pRenderer, 8);

    TextureManager::Instance()->load("assets/03-Pig/Idle (34x28).png",
                                     "enemy_pig idle", m_pRenderer, 11);
    TextureManager::Instance()->load("assets/03-Pig/Run (34x28).png",
                                     "enemy_pig run", m_pRenderer, 6);
    TextureManager::Instance()->load("assets/03-Pig/Jump (34x28).png",
                                     "enemy_pig jump", m_pRenderer, 1);
    TextureManager::Instance()->load("assets/03-Pig/Attack (34x28).png",
                                     "enemy_pig attack", m_pRenderer, 3);
    TextureManager::Instance()->load("assets/03-Pig/Dead (34x28).png",
                                     "enemy_pig dead", m_pRenderer, 4);
    TextureManager::Instance()->load("assets/03-Pig/Fall (34x28).png",
                                     "enemy_pig fall", m_pRenderer, 1);
    TextureManager::Instance()->load("assets/03-Pig/Ground (34x28).png",
                                     "enemy_pig ground", m_pRenderer, 1);
    TextureManager::Instance()->load("assets/03-Pig/Hit (34x28).png",
                                     "enemy_pig hit", m_pRenderer, 2);

    TextureManager::Instance()->load(
        "assets/7-Objects/11-Health Bar/Health Bar.png", "health bar",
        m_pRenderer);
    TextureManager::Instance()->load("assets/7-Objects/11-Health Bar/Heart.png",
                                     "health heart", m_pRenderer);

    GameObjectFactory::Instance()->registerType("Player", new Creator<Player>);
    GameObjectFactory::Instance()->registerType("Pig", new Creator<Pig>);
    GameStateMachine::Instance()->pushState(new PlayState());

    return true;
}

void Game::handleEvents() { InputHandler::Instance()->update(); }

void Game::update() {
    GameStateMachine::Instance()->update();
    TheCamera::Instance()->update();
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);
    GameStateMachine::Instance()->render();
    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {}
