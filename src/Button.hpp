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
    bool m_bDisabled;
    std::string m_text;
    Rectangle m_rectangle;

    std::function<void()> m_callback;
};
