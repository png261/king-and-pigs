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
    virtual void resume();
    virtual void pause();
    virtual bool exit() = 0;

    virtual std::string getStateID() const = 0;
    bool isLoaded() const;
    bool isPaused() const;

protected:
    GameState()
        : is_loaded_(false)
        , is_paused_(false)
    {}
    bool is_loaded_;
    bool is_paused_;
};
