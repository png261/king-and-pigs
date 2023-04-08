#pragma once

#include <memory>
#include "GameState.hpp"
#include "UiObject.hpp"

class WinState final : public GameState
{
public:
    ~WinState();
    WinState();
    void update() override;
    void render() override;
    bool onEnter() override;
    bool load() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    std::vector<std::unique_ptr<UiObject>> m_uiObjects;
    static const std::string s_stateID;
    bool m_bEnterMainMenu;
    bool m_bEnterExit;
};
