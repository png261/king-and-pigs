#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

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
    Uint32 m_pauseMark;
    bool m_bRunning;
    bool m_bPaused;
};

#endif
