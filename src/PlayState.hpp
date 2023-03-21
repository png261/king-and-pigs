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
    void update() override;
    void render() override;
    bool onEnter() override;
    bool load() override;
    void resume() override;
    bool onExit() override;
    std::string getStateID() const override;

    bool loadLevel();

private:
    static const std::string s_stateID;
    std::unique_ptr<Level> m_pLevel;
};
