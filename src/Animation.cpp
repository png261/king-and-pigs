#include "Animation.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"

Animation::Animation(
    const std::string textureID,
    const uint width,
    const uint height,
    const uint nFrames,
    const bool bLoop)
    : m_textureID(textureID)
    , m_width(width)
    , m_height(height)
    , m_nFrames(nFrames)
    , m_bLoop(bLoop)
    , m_timesLooped(0)
    , m_curFrame(0)
    , m_bRunning(false)
    , m_bFinished(false)
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
    m_curFrame = (m_stopwatch.delta() / time_between_frames);

    if (m_curFrame >= m_nFrames) {
        if (m_bLoop) {
            m_curFrame %= m_nFrames;
        } else {
            m_curFrame = m_nFrames - 1;
            m_bFinished = true;
        }
    }
}

void Animation::draw(const b2Vec2 position, const float angle, const bool bFlipped, const int zoom)
{
    if (!this->isRunning() || m_framerate == 0) {
        return;
    }

    TextureManager::Instance()
        ->drawFrame(m_textureID, position, m_width, m_height, 0, m_curFrame, angle, bFlipped, zoom);
}

void Animation::start()
{
    if (m_framerate == 0) {
        return;
    }

    if (this->isRunning()) {
        return;
    }

    m_curFrame = 0;
    m_timesLooped = 0;
    m_bRunning = true;
    m_stopwatch.start();
}

void Animation::restart()
{
    this->stop();
    this->start();
}

void Animation::stop()
{
    if (m_framerate == 0) {
        return;
    }

    if (!this->isRunning()) {
        return;
    }

    m_bRunning = false;
    m_stopwatch.stop();
}

bool Animation::isFinished() const
{
    return m_bFinished;
}

int Animation::getWidth() const
{
    return m_width;
}

int Animation::getHeight() const
{
    return m_height;
}
