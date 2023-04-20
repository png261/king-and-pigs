#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Cursor.hpp"
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
    std::string getLevelPath(const int level_index);
    Cursor* getCursor();

    void nextLevel();
    void setLevel(Level* const level);
    void setLevelIndex(int const level_index);

    void addDiamond(int n);
    void useDiamond(int n);
    int getDiamond() const;

    bool isDebug() const;
    void toggleDebug();

private:
    Game();

    std::unique_ptr<Window> window_;
    Level* level_;
    std::unique_ptr<Cursor> cursor_;
    int num_diamond_;
    bool is_running_;
    bool is_debug_;
    std::size_t level_index_;
    std::vector<std::string> level_files_;
};
