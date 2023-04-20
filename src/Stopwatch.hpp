#pragma once

#include "SDL.hpp"

class Stopwatch final
{
public:
    Stopwatch();
    void start();
    void stop();
    void pause();
    void resume();
    void restart();
    Uint32 delta() const;
    Uint32 currentTime() const;
    bool isRunning() const;
    bool isPaused() const;

protected:
    Uint32 start_mark_;
    Uint32 stop_mark_;
    Uint32 paused_mark_;
    bool is_running_;
    bool is_paused_;
};
