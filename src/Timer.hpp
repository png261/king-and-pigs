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
    Uint32 delta() const;
    Uint32 currentTime() const;
    bool isRunning() const;
    bool isPaused() const;

protected:
    Uint32 m_startMark;
    Uint32 m_stopMark;
    Uint32 m_pausedMark;
    bool m_bRunning;
    bool m_bPaused;
};

#endif
