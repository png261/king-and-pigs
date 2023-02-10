#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include <iostream>
#include <vector>
#include "MenuState.h"

class GameObject;

class GameOverState : public MenuState
{
public:
    virtual ~GameOverState() {}

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_gameOverID; }

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
    static void s_gameOverToMain();
    static void s_restartPlay();

    static const std::string s_gameOverID;

    std::vector<GameObject*> m_gameObjects;
};

#endif
