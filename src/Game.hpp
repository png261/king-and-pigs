#pragma once

#include <string>
#include <vector>
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
    bool m_bRunning;
    int m_currentLevel;
    std::vector<std::string> m_levelFiles;
};
