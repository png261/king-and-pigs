#pragma once

#include <memory>
#include "GameState.hpp"
#include "UiObject.hpp"

class MainMenuState final : public GameState
{
public:
    ~MainMenuState();
    MainMenuState();
    void update() override;
    void render() const override;
    bool enter() override;
    bool exit() override;
    std::string getStateID() const override;

private:
    std::vector<std::unique_ptr<UiObject>> m_uiObjects;
    static const std::string s_stateID;
    bool m_bEnterPlayState;
    bool m_bEnterQuit;
};
