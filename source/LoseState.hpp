#pragma once

#include <memory>

#include "GameState.hpp"
#include "UiObject.hpp"

class LoseState final : public GameState
{
public:
    LoseState();
    void update() override;
    void render() const override;
    bool enter() override;
    bool exit() override;
    std::string getStateID() const override;

private:
    std::vector<std::unique_ptr<UiObject>> ui_objects_;
    static const std::string kStateID_;
    bool is_enter_respawn_;
    bool is_enter_new_game_;
    bool is_enter_main_menu_;
};
