#include "Animation.hpp"
#include <iostream>
#include "Game.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"

Animation::Animation(const std::string textureID, const int nFrames, const bool bLoop)
    : m_textureID(textureID)
    , m_bRunning(false)
    , m_x(0)
    , m_y(0)
    , m_curFrame(0)
    , m_nFrames(nFrames)
    , m_bLoop(bLoop)
    , m_timesLooped(0)
{
    m_framerate = 10;
}

bool Animation::isRunning() const
{
    return m_bRunning;
}

void Animation::update()
{
    const Uint32 time_between_frames = (1000.0f / m_framerate);
    m_curFrame = (timer.delta() / time_between_frames);

    if (m_curFrame >= m_nFrames) {
        if (m_bLoop) {
            m_curFrame %= m_nFrames;
        } else {
            m_curFrame = m_nFrames - 1;
        }
    }
}

void Animation::draw(
    const b2Vec2 position,
    const int width,
    const int height,
    const float angle,
    const bool bFlipped)
{
    if (!isRunning() || m_framerate == 0) {
        return;
    }

    TextureManager::Instance()
        ->drawFrame(m_textureID, position, width, height, 0, m_curFrame, angle, bFlipped);
}

void Animation::start()
{
    if (m_framerate == 0) {
        return;
    }

    if (isRunning()) {
        return;
    }

    m_curFrame = 0;
    m_timesLooped = 0;
    m_bRunning = true;
    timer.start();
}

void Animation::restart()
{
    stop();
    start();
}

void Animation::stop()
{
    if (m_framerate == 0) {
        return;
    }

    if (!isRunning()) {
        return;
    }

    m_bRunning = false;
    timer.stop();
}
