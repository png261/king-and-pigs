#pragma once

#include "GameObject.hpp"
#include "PhysicManager.hpp"

class Camera final
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

    GameObject* target_;
    b2Vec2 position_;
    float zoom_;
};
