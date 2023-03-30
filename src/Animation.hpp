#pragma once

#include <string>
#include "PhysicWorld.hpp"
#include "Stopwatch.hpp"

class Animation final
{
public:
    Animation(
        const std::string textureID,
        const uint width,
        const uint height,
        const uint nFrames = 1,
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

    uint m_framerate;
    uint m_width;
    uint m_height;

    uint m_curFrame;
    uint m_nFrames;
    uint m_timesLooped;

    bool m_bRunning;
    bool m_bFinished;
    bool m_bLoop;
};
