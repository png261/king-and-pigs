#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GameObject.hpp"

class Camera
{
public:
    static Camera* Instance();
    void update();

    Vector2D getPosition() const;

    void setTarget(GameObject* target);
    void setPosition(const Vector2D& position);

private:
    Camera();
    ~Camera();

    GameObject* m_pTarget;
    Vector2D m_position;
};

typedef Camera TheCamera;

#endif
