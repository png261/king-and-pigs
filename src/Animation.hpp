#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include "Timer.hpp"
#include "Vector2D.hpp"

class Animation
{
public:
    Animation(
        std::string textureID,
        Vector2D position,
        int nFrames = 1,
        int framerate = 0,
        int loop = -1);
    virtual void update();
    void start();
    void stop();
    bool isRunning();

private:
    Timer timer;
    std::string m_textureID;
    unsigned int m_framerate;
    bool m_bRunning;
    Vector2D m_position;
    unsigned int m_textureWidth;
    unsigned int m_textureHeight;
    int m_curFrame;
    int m_nFrames;
    int m_loop;
    int m_timesLooped;
};

#endif
