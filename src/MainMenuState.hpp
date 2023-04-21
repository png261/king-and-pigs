#pragma once

#include <memory>

#include "GameState.hpp"
#include "UiObject.hpp"

class MainMenuState final : public GameState
{
public:
    MainMenuState();
    void update() override;
    void render() const override;
    bool enter() override;
    bool exit() override;
    std::string getStateID() const override;

private:
    std::vector<std::unique_ptr<UiObject>> ui_objects_;
    static const std::string kId_;
    bool is_enter_play_state;
    bool is_enter_quit_;
};
