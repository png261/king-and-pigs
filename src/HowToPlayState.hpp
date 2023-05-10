#pragma once

#include <memory>

#include "GameState.hpp"
#include "UiObject.hpp"

class HowToPlayState final : public GameState
{
public:
    HowToPlayState();
    void update() override;
    void render() const override;
    bool enter() override;
    bool exit() override;
    std::string getStateID() const override;

private:
    void renderControlTable();
    std::vector<std::unique_ptr<UiObject>> ui_objects_;
    static const std::string kId_;
    bool is_enter_main_menu;
};
