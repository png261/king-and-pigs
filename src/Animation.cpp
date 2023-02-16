#include "Animation.hpp"
#include <iostream>
#include "Game.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"

Animation::Animation(std::string textureID, int nFrames, bool bLoop)
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

bool Animation::isRunning()
{
    return m_bRunning;
}

void Animation::draw(int x, int y, int width, int height, bool bFlipped)
{
    if (m_framerate == 0) {
        return;
    }
    if (!isRunning()) {
        return;
    }

    int time_between_frames = (1000.0f / m_framerate);
    m_curFrame = (timer.delta() / time_between_frames);

    if (m_curFrame >= m_nFrames) {
        if (m_bLoop) {
            m_curFrame %= m_nFrames;
        } else {
            m_curFrame = m_nFrames - 1;
        }
    }

    TextureManager::Instance()->drawFrame(
        m_textureID,
        x,
        y,
        width,
        height,
        0,
        m_curFrame,
        Game::Instance()->getRenderer(),
        bFlipped);
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
