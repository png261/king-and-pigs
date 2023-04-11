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
    std::vector<std::unique_ptr<UiObject>> m_uiObjects;
    static const std::string s_stateID;
    bool m_bEnterMainMenu;
    bool m_bEnterExit;
};
