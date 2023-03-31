#pragma once
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
    static void s_resume();
    static void s_mainMenu();
    std::vector<UiObject*> m_uiObjects;
    static const std::string s_stateID;
};
