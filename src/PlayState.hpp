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
    void render() override;
    bool onEnter() override;
    bool load() override;
    void resume() override;
    bool onExit() override;
    std::string getStateID() const override;

    bool loadLevel();
    void loadNewLevel();

private:
    static void s_mute();

    bool m_bDebug;
    static const std::string s_stateID;
    std::unique_ptr<Level> m_pLevel;
};
