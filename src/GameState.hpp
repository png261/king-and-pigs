#pragma once

#include <string>
#include <vector>

class GameState
{
public:
    virtual ~GameState(){};
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool load() = 0;
    virtual void resume(){};
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;

protected:
    GameState()
        : m_loadingComplete(false)
        , m_exiting(false)
    {}
    bool m_loadingComplete;
    bool m_exiting;
};

