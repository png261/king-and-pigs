#include "Timer.hpp"

Timer::Timer()
    : time_(0)
    , is_done_(false)
{}

Timer::Timer(const Uint32 time)
    : time_(time)
    , is_done_(false)
{}

void Timer::setTime(const Uint32 time)
{
    time_ = time;
}

void Timer::start()
{
    stopwatch_.start();
}

void Timer::restart()
{
    stopwatch_.restart();
}

bool Timer::isDone()
{
    if (stopwatch_.delta() >= time_) {
        stopwatch_.stop();
        return true;
    }
    return false;
}
