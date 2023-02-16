#include "Timer.hpp"
#include <iostream>

Timer::Timer()
{
    m_startMark = 0;
    m_stopMark = 0;
    m_pausedMark = 0;
    m_bRunning = false;
    m_bPaused = false;
}

void Timer::start()
{
    if (isRunning()) {
        return;
    }

    m_startMark = SDL_GetTicks();
    m_stopMark = 0;
    m_pausedMark = 0;
    m_bRunning = true;
    m_bPaused = false;
}

void Timer::stop()
{
    if (!isRunning()) {
        return;
    }

    m_stopMark = SDL_GetTicks();
    m_bRunning = false;
    m_bPaused = false;
}

void Timer::restart()
{
    stop();
    start();
}

void Timer::pause()
{
    if (!isRunning() || isPaused()) {
        return;
    }
    m_bRunning = false;
    m_bPaused = true;
    m_pausedMark = (SDL_GetTicks() - this->m_startMark);
}

void Timer::resume()
{
    if (isRunning() || !isPaused()) {
        return;
    }

    m_bRunning = false;
    m_bPaused = true;
    m_startMark = (SDL_GetTicks() - this->m_pausedMark);
    m_pausedMark = 0;
}

bool Timer::isRunning()
{
    return m_bRunning;
}

bool Timer::isPaused()
{
    return m_bPaused;
}

Uint32 Timer::currentTime()
{
    return SDL_GetTicks() - m_startMark;
}

Uint32 Timer::delta()
{
    if (isRunning()) {
        return currentTime();
    }

    if (isPaused()) {
        return m_pausedMark;
    }

    if (m_startMark == 0) {
        return 0;
    }

    return m_stopMark - m_startMark;
}
