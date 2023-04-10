#pragma once

#include "GameObject.hpp"
#include "PhysicWorld.hpp"

class Camera
{
public:
    static Camera& Instance();
    Camera(Camera const&) = delete;
    Camera& operator=(Camera const&) = delete;

    void update();

    b2Vec2 getPosition() const;
    float getZoom() const;

    void setTarget(GameObject* const target);
    void setPosition(const b2Vec2& position);
    void setZoom(const float zoom);

private:
    Camera();

    GameObject* m_pTarget;
    b2Vec2 m_position;
    float m_zoom;
};

typedef Camera Camera;
