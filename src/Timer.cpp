#include "Timer.hpp"

Timer::Timer()
    : m_time(0)
    , m_bDone(false)
{}

Timer::Timer(Uint32 time)
    : m_time(time)
    , m_bDone(false)
{}

void Timer::setTime(Uint32 time)
{
    m_time = time;
}

void Timer::start()
{
    m_stopwatch.start();
}

void Timer::restart()
{
    m_stopwatch.restart();
}

bool Timer::isDone()
{
    if (m_stopwatch.delta() >= m_time) {
        m_stopwatch.stop();
        return true;
    }
    return false;
}
