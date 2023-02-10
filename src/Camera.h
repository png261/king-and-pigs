#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera
{
public:
    static Camera* Instance()
    {
        static Camera* s_pCamera = new Camera();
        return s_pCamera;
    }

    void update();

    void setTarget(GameObject* target) { m_pTarget = target; }
    void setPosition(const Vector2D& position) { m_position = position; }

    Vector2D getPosition() const;

private:
    Camera();
    ~Camera();

    GameObject* m_pTarget;

    Vector2D m_position;
};

typedef Camera TheCamera;

#endif
