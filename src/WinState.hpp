#pragma once

#include <memory>

#include "GameState.hpp"
#include "UiObject.hpp"

class WinState final : public GameState
{
public:
    WinState();
    void update() override;
    void render() const override;
    bool enter() override;
    bool exit() override;
    std::string getStateID() const override;

private:
    std::vector<std::unique_ptr<UiObject>> ui_objects_;
    static const std::string kId_;
    bool is_enter_main_menu_;
    bool is_enter_exit_;
};
