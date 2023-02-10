#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include <iostream>
#include <vector>
#include "MenuState.h"

class GameObject;

class PauseState : public MenuState
{
public:
    virtual ~PauseState() {}

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_stateID; }

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
    static void s_pauseToMain();
    static void s_resumePlay();

    static const std::string s_stateID;

    std::vector<GameObject*> m_gameObjects;
};

#endif
