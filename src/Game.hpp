#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Level.hpp"
#include "Window.hpp"

class Game final
{
public:
    static Game* Instance();

    bool init();
    void handleEvents();
    void update();
    void render();
    void clean();
    void quit();
    bool isRunning() const;

    Window* getWindow();
    int getLevelIndex() const;
    void nextLevel();
    std::string getLevelPath(const int index);

    void setLevelIndex(int const currentLevel);

    void setLevel(Level* const pLevel);
    Level* getLevel();

private:
    Game();
    ~Game();
    Window* m_pWindow;
    Level* m_pLevel;
    bool m_bRunning;
    int m_levelIndex;
    std::vector<std::string> m_levelFiles;
};
