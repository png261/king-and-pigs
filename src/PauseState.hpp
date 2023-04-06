#pragma once

#include <memory>
#include "GameState.hpp"
#include "UiObject.hpp"

class PauseState final : public GameState
{
public:
    ~PauseState();
    PauseState();
    void update() override;
    void render() override;
    bool onEnter() override;
    bool load() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    void s_resume();
    void s_mainMenu();
    std::vector<std::unique_ptr<UiObject>> m_uiObjects;
    static const std::string s_stateID;
};
