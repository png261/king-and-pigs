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
    ~Button();
    void draw();
    void update();
    void onClick(std::function<void()> callback);

private:
    Rectangle m_rectangle;
    std::string m_text;

    std::function<void()> m_callback;
};
