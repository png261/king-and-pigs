#ifndef PLAY_STATE_HPP
#define PLAY_STATE_HPP

#include <vector>
#include "GameObject.hpp"
#include "GameState.hpp"
#include "Level.hpp"

class PlayState final : public GameState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool load();
    virtual void resume();
    virtual bool onExit();
    virtual std::string getStateID() const { return s_stateID; }

private:
    static const std::string s_stateID;
    std::vector<GameObject*> m_gameObjects;
    Level* pLevel;
};

#endif
