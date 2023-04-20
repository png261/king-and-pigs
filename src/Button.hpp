#pragma once
#include <functional>
#include <unordered_map>
#include "Animation.hpp"
#include "Shapes.hpp"
#include "UiObject.hpp"

class Button final : public UiObject
{
public:
    Button(std::string text, int x, int y, int width, int height);
    void draw();
    void update();
    void onClick(std::function<void()> callback);
    void disable();
    void enable();
    bool isDisabled() const;

private:
    bool is_disabled_;
    std::string text_;
    Rectangle rectangle_;

    std::function<void()> callback_;
};
