#include "Stopwatch.hpp"

Stopwatch::Stopwatch()
{
    m_startMark = 0;
    m_stopMark = 0;
    m_pausedMark = 0;
    m_bRunning = false;
    m_bPaused = false;
}

void Stopwatch::start()
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

void Stopwatch::stop()
{
    if (!isRunning()) {
        return;
    }

    m_stopMark = SDL_GetTicks();
    m_bRunning = false;
    m_bPaused = false;
}

void Stopwatch::restart()
{
    stop();
    start();
}

void Stopwatch::pause()
{
    if (!isRunning() || isPaused()) {
        return;
    }
    m_bRunning = false;
    m_bPaused = true;
    m_pausedMark = (SDL_GetTicks() - this->m_startMark);
}

void Stopwatch::resume()
{
    if (isRunning() || !isPaused()) {
        return;
    }

    m_bRunning = false;
    m_bPaused = true;
    m_startMark = (SDL_GetTicks() - this->m_pausedMark);
    m_pausedMark = 0;
}

bool Stopwatch::isRunning() const
{
    return m_bRunning;
}

bool Stopwatch::isPaused() const
{
    return m_bPaused;
}

Uint32 Stopwatch::currentTime() const
{
    return SDL_GetTicks() - m_startMark;
}

Uint32 Stopwatch::delta() const
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
