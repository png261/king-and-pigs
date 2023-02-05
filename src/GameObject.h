#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "LoaderParams.h"
#include "Vector2D.h"
#include <string>
#include <vector>

class GameObject {
  public:
    virtual void load(const LoaderParams *pParams) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void clean() = 0;

    virtual void collision() = 0;

    virtual std::string type() = 0;

    Vector2D &getPosition() { return m_position; }
    Vector2D &getVelocity() { return m_velocity; }

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

  protected:
    // constructor with default initialisation list
    GameObject()
        : m_position(0, 0), m_velocity(0, 0), m_acceleration(0, 0), m_width(0),
          m_height(0), m_currentRow(0), m_currentFrame(0), m_bUpdating(false),
          m_bDead(false), m_bDying(false), m_angle(0), m_alpha(255), m_bFlipped(false) {}

    // movement
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    // size
    int m_width;
    int m_height;

    // animation
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;

    // common boolean
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;

    // rotation
    double m_angle;
    bool m_bFlipped;

    // blending
    int m_alpha;
};

#endif
