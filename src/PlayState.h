#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <vector>
#include "GameObject.h"
#include "GameState.h"
#include "Level.h"

class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onExit();
    virtual void resume();
    virtual bool onEnter();
    virtual std::string getStateID() const { return s_stateID; }

private:
    static const std::string s_stateID;
    std::vector<GameObject*> m_gameObjects;
    Level* pLevel;
};

#endif
