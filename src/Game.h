#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Game {
  public:
    static Game *Instance() {
        static Game *s_pInstance = new Game();
        return s_pInstance;
    }
    bool init(const char *title, int x, int y, int w, int h, Uint32 flags);
    void handleEvents();
    void update();
    void render();
    void clean();

    SDL_Renderer *getRenderer() { return m_pRenderer; }

    void setPlayerLives(int lives) { m_playerLives = lives; }
    int getPlayerLives() { return m_playerLives; }

    void setCurrentLevel(int currentLevel);
    int getCurrentLevel() const { return m_currentLevel; }

    void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
    int getNextLevel() const { return m_nextLevel; }

    void setLevelComplete(bool levelComplete) {
        m_bLevelComplete = levelComplete;
    }
    const bool getLevelComplete() { return m_bLevelComplete; }

    bool running() { return m_bRunning; }

    void quit() { m_bRunning = false; }

    int getGameWidth() const { return m_gameWidth; }
    int getGameHeight() const { return m_gameHeight; }
    void setLevelWidth(int width) { m_levelWidth = width; }
    void setLevelHeight(int height) { m_levelHeight = height; }

    int getLevelWidth() { return m_levelWidth; }
    int getLevelHegith() { return m_levelHeight; }

    std::vector<std::string> getLevelFiles() { return m_levelFiles; }

  private:
    Game();
    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    int m_gameWidth;
    int m_gameHeight;

    int m_levelWidth;
    int m_levelHeight;

    bool m_bRunning;

    int m_playerLives;

    int m_currentLevel;
    int m_nextLevel;
    bool m_bLevelComplete;

    std::vector<std::string> m_levelFiles;
};

typedef Game TheGame;

#endif
