#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Level.hpp"
#include "Window.hpp"

class Game final
{
public:
    ~Game();

    static Game* Instance();

    bool init();
    void handleEvents();
    void update();
    void render();
    void clean();
    void quit();

    Window* getWindow();
    bool isRunning() const;
    bool isDebug() const;
    int getCurrentLevel() const;
    int getNextLevel() const;
    void nextLevel();
    std::string loadLevel(const int index);

    void setCurrentLevel(int const currentLevel);

    void setLevel(Level* const pLevel);
    Level* getLevel();

private:
    Game();
    Window* m_pWindow;
    Level* m_pLevel;
    bool m_bRunning;
    bool m_bDebug;
    int m_currentLevel;
    std::vector<std::string> m_levelFiles;
};
