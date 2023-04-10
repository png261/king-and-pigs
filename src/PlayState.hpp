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
    PlayState();
    void update() override;
    void render() const override;
    bool enter() override;
    void resume() override;
    bool exit() override;
    std::string getStateID() const override;
    bool loadLevel();

private:
    static const std::string s_stateID;
    std::shared_ptr<Level> m_pLevel;
};
