#pragma once

#include <string>

#include "PhysicWorld.hpp"
#include "Stopwatch.hpp"

class Animation final
{
public:
    Animation(
        const std::string& texture_id,
        const uint width,
        const uint height,
        const uint num_frames = 1,
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

    uint width_;
    uint height_;
    uint framerate_;

    uint num_frames_;
    uint current_frame_;
    uint times_looped_;

    bool is_running_;
    bool is_finished_;
    bool is_loop_;
};
