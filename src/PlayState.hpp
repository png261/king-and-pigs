#pragma once

#include <memory>
#include <vector>

#include "GameObject.hpp"
#include "GameState.hpp"
#include "Level.hpp"

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

private:
    void renderStatusBar() const;

    static const std::string kId_;
    std::unique_ptr<Level> level_;
};
