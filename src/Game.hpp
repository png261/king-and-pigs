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

    bool init();
    void handleEvents();
    void update();
    void render() const;
    void clean();
    void quit();
    bool isRunning() const;

    std::shared_ptr<Window> getWindow() const;
    std::shared_ptr<Level> getLevel() const;
    int getLevelIndex() const;
    std::string getLevelPath(const int index);

    void nextLevel();
    void setLevel(std::shared_ptr<Level> const& pLevel);
    void setLevelIndex(int const currentLevel);

    bool isDebug() const;
    void toggleDebug();

private:
    Game();

    std::shared_ptr<Window> m_pWindow;
    std::shared_ptr<Level> m_pLevel;
    bool m_bRunning;
    bool m_bDebug;
    int m_levelIndex;
    std::vector<std::string> m_levelFiles;
};
