#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include "Box2D.hpp"
#include "Timer.hpp"

class Animation
{
public:
    enum AnimationID {
        IDLE,
        RUN,
        JUMP,
        FALL,
        GROUND,
        ATTACK,
        DEAD,
        HIT,

        DOOR_IN,
        DOOR_OUT,
        DOOR_OPEN,
        DOOR_CLOSE,
    };

    Animation(const std::string textureID, const int nFrames = 1, const bool bLoop = true);

    virtual void draw(
        const b2Vec2 position,
        const int width,
        const int height,
        const float angle = 0,
        const bool flip = false);

    void start();
    void restart();
    void stop();
    bool isRunning() const;

private:
    Timer timer;
    std::string m_textureID;
    unsigned int m_framerate;

    bool m_bRunning;
    int m_x;
    int m_y;

    unsigned int m_width;
    unsigned int m_height;

    int m_curFrame;
    int m_nFrames;
    bool m_bLoop;
    int m_timesLooped;
};

#endif
