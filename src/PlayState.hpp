#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include <vector>
#include "GameObject.hpp"
#include "GameState.hpp"
#include "Level.hpp"

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
