#pragma once

#include <string>
#include "PhysicWorld.hpp"
#include "Stopwatch.hpp"

class Animation final
{
public:
    Animation(
        const std::string textureID,
        const int width,
        const int height,
        const int nFrames = 1,
        const bool bLoop = true);
    virtual ~Animation();

    virtual void draw(const b2Vec2 position, const float angle = 0, const bool flip = false);
    virtual void update();

    void start();
    void restart();
    void stop();
    bool isRunning() const;
    bool isFinished() const;
    int getWidth() const;
    int getHeight() const;

private:
    Stopwatch m_stopwatch;
    std::string m_textureID;
    unsigned int m_framerate;

    bool m_bRunning;
    bool m_bFinished;

    unsigned int m_width;
    unsigned int m_height;

    int m_curFrame;
    int m_nFrames;
    bool m_bLoop;
    int m_timesLooped;
};
