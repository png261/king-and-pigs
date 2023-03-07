#ifndef GAME_HPP
#define GAME_HPP

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
    std::string getLevel(int index);
    bool isRunning() const;

    void setCurrentLevel(int const currentLevel);
    void setPlayer(Player* const pPlayer);

private:
    Game();
    Window* m_pWindow;

    int m_currentLevel;

    bool m_bRunning;

    Player* m_pPlayer;

    std::vector<std::string> m_levelFiles;
};

#endif
