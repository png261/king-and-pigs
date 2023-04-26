#include "Animation.hpp"

#include "Game.hpp"
#include "Log.hpp"
#include "TextureManager.hpp"

Animation::Animation(
    const std::string& texture_id,
    const uint width,
    const uint height,
    const uint num_frames,
    const bool bLoop)
    : texture_id_(texture_id)
    , width_(width)
    , height_(height)
    , framerate_(10)
    , num_frames_(num_frames)
    , current_frame_(0)
    , times_looped_(0)
    , is_running_(false)
    , is_finished_(false)
    , is_loop_(bLoop)
{}

bool Animation::isRunning() const
{
    return is_running_;
}

void Animation::update()
{
    if (framerate_ == 0) {
        return;
    }

    const Uint32 time_between_frames = (1000 / framerate_);
    current_frame_ = (stopwatch_.delta() / time_between_frames);

    if (current_frame_ >= num_frames_) {
        if (is_loop_) {
            current_frame_ %= num_frames_;
        } else {
            current_frame_ = num_frames_ - 1;
            is_finished_ = true;
        }
    }
}

void Animation::draw(const b2Vec2& position, const float angle, const bool is_flip, const int zoom)
    const
{
    if (!isRunning()) {
        return;
    }

    TextureManager::Instance()
        .drawFrame(texture_id_, position, width_, height_, 0, current_frame_, angle, is_flip, zoom);
}

void Animation::start()
{
    if (framerate_ == 0 || isRunning()) {
        return;
    }

    current_frame_ = 0;
    times_looped_ = 0;
    is_running_ = true;
    stopwatch_.start();
}

void Animation::restart()
{
    stop();
    start();
}

void Animation::stop()
{
    if (framerate_ == 0) {
        return;
    }

    if (!isRunning()) {
        return;
    }

    is_running_ = false;
    stopwatch_.stop();
}

bool Animation::isFinished() const
{
    return is_finished_;
}

int Animation::getWidth() const
{
    return width_;
}

int Animation::getHeight() const
{
    return height_;
}
