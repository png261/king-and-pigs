#pragma once
#include "SDL.hpp"
#include "Stopwatch.hpp"

class Timer final
{
public:
    Timer(Uint32 time);
    Timer();
    void setTime(Uint32 time);
    void start();
    void restart();
    bool isDone();
    bool isRunning();

private:
    Uint32 time_;
    bool is_done_;
    Stopwatch stopwatch_;
};
