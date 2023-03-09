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
    int getCurrentLevel() const;
    int getNextLevel() const;
    Player* getPlayer() const;
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
