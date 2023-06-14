#pragma once

#include <memory>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

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
    void handleFPS() const;
    void clean();
    void quit();
    void debugMode(bool is_debug);

    void handleWin();
    void handleLose();

    bool isRunning() const;
    bool isDebug() const;
    nlohmann::json getConfig() const;
    Window* getWindow() const;
    Cursor* getCursor() const;
    Level* getLevel() const;
    int getLevelIndex() const;
    std::string getLevelPath(const int level_index) const;
    std::string getCurrentLevelPath() const;
    int getDiamond() const;
    int getScore() const;
    int getTopScore() const;

    void nextLevel();
    void setLevel(Level* const level);
    void setLevelIndex(int const level_index);
    void resetLevel();
    bool isLastLevel() const;

    void addDiamond(const int n);
    void useDiamond(const int n);

    void resetScore();
    void addScore(const int score);

private:
    Game();
    void readConfig();
    void createWindow();
    void createCursor();
    void loadLevel();

    nlohmann::json config_;
    SDL_Event event_;

    std::unique_ptr<Window> window_;
    std::unique_ptr<Cursor> cursor_;
    Level* level_;
    int num_diamond_;
    bool is_running_;
    bool is_debug_;
    std::size_t level_index_;
    std::vector<std::string> level_files_;
    int top_score_;
    int score_;
};
