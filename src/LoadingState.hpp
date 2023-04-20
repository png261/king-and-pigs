#pragma once

#include <memory>
#include "GameState.hpp"
#include "UiObject.hpp"

class LoadingState final : public GameState
{
public:
    LoadingState();
    void update() override;
    void render() const override;
    bool enter() override;
    bool exit() override;
    std::string getStateID() const override;

private:
    std::vector<std::unique_ptr<UiObject>> ui_objects_;
    static const std::string kId_;
};
