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
    void render() const override;
    bool onEnter() override;
    bool load() override;
    bool onExit() override;
    std::string getStateID() const override;

private:
    std::vector<std::unique_ptr<UiObject>> m_uiObjects;
    static const std::string s_stateID;
    bool m_bEnterResume;
    bool m_bEnterMainMenu;
};
