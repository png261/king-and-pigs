#include "Timer.h"

Timer::Timer()
    : m_startMark(0)
    , m_stopMark(0)
    , m_pauseMark(0)
    , m_bRunning(false)
    , m_bPaused(false)
{}

void Timer::start()
{
    if (m_bRunning) {
        return;
    }

    m_startMark = SDL_GetTicks();
    m_stopMark = 0;
    m_pauseMark = 0;
    m_bRunning = true;
    m_bPaused = false;
}

void Timer::stop()
{
    if (!m_bRunning) {
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
    if (!m_bRunning || m_bPaused) {
        return;
    }
    m_bRunning = false;
    m_bPaused = true;
    m_pauseMark = (SDL_GetTicks() - this->m_startMark);
}

void Timer::resume()
{
    if (m_bRunning || !m_bPaused) {
        return;
    }

    m_bRunning = false;
    m_bPaused = true;
    m_startMark = (SDL_GetTicks() - this->m_pauseMark);
    m_pauseMark = 0;
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
        return m_pauseMark;
    }

    if (m_startMark == 0) {
        return 0;
    }

    return m_stopMark - m_startMark;
}
