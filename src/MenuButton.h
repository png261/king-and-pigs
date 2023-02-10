#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "GameObjectFactory.h"
#include "PlatformerObject.h"

class MenuButton : public PlatformerObject
{
public:
    MenuButton();

    virtual ~MenuButton() {}

    virtual void load(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    void setCallback(void (*callback)()) { m_callback = callback; }
    int getCallbackID() { return m_callbackID; }

private:
    enum button_state { MOUSE_OUT = 0, MOUSE_OVER = 1, CLICKED = 2 };

    bool m_bReleased;

    int m_callbackID;

    void (*m_callback)();
};

#endif