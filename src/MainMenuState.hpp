#pragma once
#include "GameState.hpp"
#include "UiObject.hpp"

class MainMenuState final : public GameState
{
public:
    ~MainMenuState();
    MainMenuState();
    void update();
    void render();
    bool onEnter();
    bool load();
    void resume();
    bool onExit();
    std::string getStateID() const;

private:
    static void s_enterPlay();
    static void s_exit();
    std::vector<UiObject*> m_uiObjects;
    static const std::string s_stateID;
};
