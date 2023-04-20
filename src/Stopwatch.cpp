#include "Stopwatch.hpp"

Stopwatch::Stopwatch()
{
    start_mark_ = 0;
    stop_mark_ = 0;
    paused_mark_ = 0;
    is_running_ = false;
    is_paused_ = false;
}

void Stopwatch::start()
{
    if (isRunning()) {
        return;
    }

    start_mark_ = SDL_GetTicks();
    stop_mark_ = 0;
    paused_mark_ = 0;
    is_running_ = true;
    is_paused_ = false;
}

void Stopwatch::stop()
{
    if (!isRunning()) {
        return;
    }

    stop_mark_ = SDL_GetTicks();
    is_running_ = false;
    is_paused_ = false;
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
    is_running_ = false;
    is_paused_ = true;
    paused_mark_ = (SDL_GetTicks() - start_mark_);
}

void Stopwatch::resume()
{
    if (isRunning() || !isPaused()) {
        return;
    }

    is_running_ = false;
    is_paused_ = true;
    start_mark_ = (SDL_GetTicks() - paused_mark_);
    paused_mark_ = 0;
}

bool Stopwatch::isRunning() const
{
    return is_running_;
}

bool Stopwatch::isPaused() const
{
    return is_paused_;
}

Uint32 Stopwatch::currentTime() const
{
    return SDL_GetTicks() - start_mark_;
}

Uint32 Stopwatch::delta() const
{
    if (isRunning()) {
        return currentTime();
    }

    if (isPaused()) {
        return paused_mark_;
    }

    if (start_mark_ == 0) {
        return 0;
    }

    return stop_mark_ - start_mark_;
}
