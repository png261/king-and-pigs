#pragma once

#include "SDL.hpp"
#include "Stopwatch.hpp"

class Timer final
{
public:
    Timer();
    Timer(const Uint32 time);
    void setTime(const Uint32 time);
    void start();
    void restart();
    bool isDone();
    bool isRunning() const;

private:
    Uint32 time_;
    bool is_done_;
    Stopwatch stopwatch_;
};
