#pragma once
#include <map>
#include "Animation.hpp"
#include "Shapes.hpp"
#include "UiObject.hpp"

class Button final : public UiObject
{
public:
    Button(std::string text, int x, int y, int width, int height);
    ~Button();
    void load();
    void draw();
    void update();
    void setCallback(void (*callback)());

private:
    enum { NORMAL, HOVERED, PRESSED };

    Rectangle m_rectangle;
    std::string m_text;

    int m_curAnimation;
    std::map<int, Animation*> m_animations;

    bool m_bHovered;

    void (*m_callback)();
};
