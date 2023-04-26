#pragma once

#include <functional>
#include <unordered_map>

#include "Animation.hpp"
#include "Shapes.hpp"
#include "UiObject.hpp"

class Button final : public UiObject
{
public:
    Button(
        const std::string& text,
        const int x,
        const int y,
        const int width,
        const int height,
        const float border_radius = 20.0f);
    void draw();
    void update();
    void onClick(const std::function<void()>& callback);
    void disable();
    void enable();
    bool isDisabled() const;

private:
    bool is_disabled_;
    std::string text_;
    Rectangle rectangle_;

    std::function<void()> callback_;
};
