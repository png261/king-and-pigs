#pragma once

#include <string>
#include <vector>
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
    void nextLevel();
    std::string getLevel(const int index);
    bool isRunning() const;

    void setCurrentLevel(int const currentLevel);

private:
    Game();

    Window* m_pWindow;

    int m_currentLevel;

    bool m_bRunning;

    std::vector<std::string> m_levelFiles;
};
