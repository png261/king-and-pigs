#ifndef MENU_STATE
#define MENU_STATE

#include "GameState.hpp"

class MenuState : public GameState
{
public:
    virtual ~MenuState() {}

protected:
    typedef void (*Callback)();
    virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;

    std::vector<Callback> m_callbacks;
};

#endif
