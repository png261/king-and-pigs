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
    void render() override;
    bool onEnter() override;
    bool load() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    void s_enterPlay();
    void s_exit();
    std::vector<std::unique_ptr<UiObject>> m_uiObjects;
    static const std::string s_stateID;
};
