#pragma once

#include <memory>
#include <vector>

#include "GameObject.hpp"
#include "GameState.hpp"
#include "Level.hpp"
#include "LevelParser.hpp"

class PlayState final : public GameState
{
public:
    PlayState();
    void update() override;
    void render() const override;
    bool enter() override;
    bool exit() override;
    std::string getStateID() const override;
    bool loadLevel();
    Level* getLevel() const;

private:
    void renderStatusBar() const;

    LevelParser level_parser_;
    static const std::string kStateID_;
    std::unique_ptr<Level> level_;
};
