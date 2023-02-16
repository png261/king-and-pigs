#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "Player.hpp"

class Game
{
public:
    ~Game(){};
    static Game* Instance();
    bool init(const char* title, int x, int y, int w, int h, Uint32 flags);
    void handleEvents();
    void update();
    void render();
    void clean();
    void quit();

    SDL_Renderer* getRenderer();
    int getCurrentLevel() const;
    int getNextLevel() const;
    const bool isLevelComplete();
    int getGameWidth() const;
    int getGameHeight() const;
    int getLevelWidth();
    int getLevelHegith();
    Player* getPlayer();
    std::vector<std::string> getLevelFiles();

    bool isRunning();

    void setCurrentLevel(int currentLevel);
    void setNextLevel(int nextLevel);
    void setLevelComplete(bool levelComplete);
    void setLevelWidth(int width);
    void setLevelHeight(int height);
    void setPlayer(Player* pPlayer);

private:
    Game();

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_gameWidth;
    int m_gameHeight;

    int m_levelWidth;
    int m_levelHeight;

    bool m_bRunning;

    int m_currentLevel;
    int m_nextLevel;
    bool m_bLevelComplete;

    Player* m_pPlayer;

    std::vector<std::string> m_levelFiles;
};

typedef Game TheGame;

#endif
