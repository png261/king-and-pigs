#pragma once

#include <vector>
#include "GameObject.hpp"
#include "GameState.hpp"
#include "Level.hpp"

class PlayState final : public GameState
{
public:
    void update();
    void render();

    bool onEnter();
    bool load();
    bool loadLevel();
    void resume();
    bool onExit();
    std::string getStateID() const { return s_stateID; }

private:
    static const std::string s_stateID;
    std::vector<GameObject*> m_gameObjects;
    Level* m_pLevel;
};
