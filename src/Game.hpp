#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Level.hpp"
#include "Window.hpp"

class Game final
{
public:
    static Game& Instance();
    Game(Game const&) = delete;
    Game& operator=(Game const&) = delete;

    void init();
    void handleEvents();
    void update();
    void render() const;
    void clean();
    void quit();
    bool isRunning() const;

    Window* getWindow() const;
    Level* getLevel() const;
    int getLevelIndex() const;
    std::string getLevelPath(const int index);

    void nextLevel();
    void setLevel(Level* const pLevel);
    void setLevelIndex(int const currentLevel);

    void addDiamond(int n);
    void useDiamond(int n);
    int getDiamond() const;

    bool isDebug() const;
    void toggleDebug();

private:
    Game();

    std::unique_ptr<Window> m_pWindow;
    Level* m_pLevel;
    int m_nDiamond;
    bool m_bRunning;
    bool m_bDebug;
    std::size_t m_levelIndex;
    std::vector<std::string> m_levelFiles;
};
