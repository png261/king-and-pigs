#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Box2D.hpp"
#include "GameObject.hpp"

class Camera
{
public:
    static Camera* Instance();
    void update();

    b2Vec2 getPosition() const;

    void setTarget(GameObject* target);
    void setPosition(const b2Vec2& position);

private:
    Camera();
    ~Camera();

    GameObject* m_pTarget;
    b2Vec2 m_position;
};

typedef Camera TheCamera;

#endif
