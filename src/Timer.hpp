#ifndef TIMER_HPP
#define TIMER_HPP

#include "SDL.hpp"

class Timer
{
public:
    Timer();
    void start();
    void stop();
    void pause();
    void resume();
    void restart();
    Uint32 delta();
    Uint32 currentTime();
    bool isRunning();
    bool isPaused();

protected:
    Uint32 m_startMark;
    Uint32 m_stopMark;
    Uint32 m_pausedMark;
    bool m_bRunning;
    bool m_bPaused;
};

#endif
