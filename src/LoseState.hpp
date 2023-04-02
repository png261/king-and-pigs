#pragma once
#include "GameState.hpp"
#include "UiObject.hpp"

class LoseState final : public GameState
{
public:
    ~LoseState();
    LoseState();
    void update() override;
    void render() override;
    bool onEnter() override;
    bool load() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    static void s_mainMenu();
    static void s_exit();
    std::vector<UiObject*> m_uiObjects;
    static const std::string s_stateID;
};
