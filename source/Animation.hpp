#pragma once

#include <string>

#include "PhysicManager.hpp"
#include "Stopwatch.hpp"

class Animation final
{
public:
    Animation(
        const std::string& texture_id,
        const int width,
        const int height,
        const int num_frames = 1,
        const bool is_loop = true);

    void draw(
        const b2Vec2& position,
        const float angle = 0,
        const bool is_flip = false,
        const int zoom = 1) const;

    void update();

    void start();
    void restart();
    void stop();

    bool isRunning() const;
    bool isFinished() const;
    int getWidth() const;
    int getHeight() const;

private:
    Stopwatch stopwatch_;
    std::string texture_id_;

    int width_;
    int height_;
    int framerate_;

    int num_frames_;
    int current_frame_;
    int times_looped_;

    bool is_running_;
    bool is_finished_;
    bool is_loop_;
};
