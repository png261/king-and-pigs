#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include "Timer.hpp"

class Animation
{
public:
    Animation(std::string textureID, int nFrames = 1, bool bLoop = true);

    virtual void draw(int x, int y, int width, int height, float angle = 0, bool flip = false);
    void start();
    void restart();
    void stop();
    bool isRunning();

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
