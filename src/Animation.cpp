#include "Animation.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

Animation::Animation(
    std::string textureID,
    Vector2D position,
    int nFrames,
    int framerate,
    int loops)
    : m_textureID(textureID)
    , m_framerate(framerate)
    , m_bRunning(false)
    , m_position(position)
    , m_curFrame(0)
    , m_nFrames(nFrames)
    , m_loop(loops)
    , m_timesLooped(0)
{}

bool Animation::isRunning()
{
    return m_bRunning;
}

void Animation::update()
{
    if (m_framerate == 0) {
        return;
    }
    if (m_bRunning == false) {
        return;
    }

    int time_between_frames = (1000 / m_framerate);
    int frame_passed = timer.delta() / time_between_frames;

    if (frame_passed == 0) {
        timer.pause();
        return;
    }
}

void Animation::stop() {}
