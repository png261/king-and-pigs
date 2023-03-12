#pragma once

#include <string>
#include <vector>
#include "Player.hpp"
#include "SDL.hpp"
#include "Window.hpp"

class Game final
{
public:
    ~Game(){};

    static Game* Instance();
    bool init(const unsigned int width, const unsigned int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    void quit();

    Window* getWindow();
    Player* getPlayer() const;
    int getCurrentLevel() const;
    int getNextLevel() const;
    void nextLevel();
    std::string getLevel(const int index);
    bool isRunning() const;

    void setCurrentLevel(int const currentLevel);
    void setPlayer(Player* const pPlayer);

private:
    Game();
    Player* m_pPlayer;
    Window* m_pWindow;

    int m_currentLevel;

    bool m_bRunning;

    std::vector<std::string> m_levelFiles;
};
