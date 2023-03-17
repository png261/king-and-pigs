#pragma once

#include <memory>
#include <vector>
#include "GameObject.hpp"
#include "GameState.hpp"
#include "Level.hpp"

class PlayState final : public GameState
{
public:
    ~PlayState();
    void update();
    void render();

    bool onEnter();
    bool load();
    bool loadLevel();
    void resume();
    bool onExit();
    std::string getStateID() const;

private:
    static const std::string s_stateID;
    std::unique_ptr<Level> m_pLevel;
};
