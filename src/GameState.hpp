#pragma once

#include <string>
#include <vector>

class GameState
{
public:
    virtual ~GameState() = default;
    virtual void update() = 0;
    virtual void render() const = 0;

    virtual bool enter() = 0;
    virtual void resume(){};
    virtual bool exit() = 0;

    virtual std::string getStateID() const = 0;

protected:
    GameState()
        : m_bLoaded(false)
        , m_bPaused(false)
    {}
    bool m_bLoaded;
    bool m_bPaused;
};
