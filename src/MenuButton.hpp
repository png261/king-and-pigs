#ifndef MENU_BUTTON_HPP
#define MENU_BUTTON_HPP

#include "GameObjectFactory.hpp"
#include "PlatformerObject.hpp"

class MenuButton : public PlatformerObject
{
public:
    MenuButton();

    virtual ~MenuButton() {}

    virtual void load(const LoaderParams* const pParams);

    virtual void draw();
    virtual void update();

    virtual std::string type() const;

    void setCallback(void (*callback)()) { m_callback = callback; }
    int getCallbackID() { return m_callbackID; }

private:
    enum button_state { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 };

    bool m_bReleased;
    int m_currentFrame;

    int m_callbackID;

    void (*m_callback)();
};

#endif
