#include "Box.hpp"
#include "Box2D.hpp"

Box::Box()
    : PlatformerObject()
{}

void Box::load(const LoaderParams* pParams)
{
    PlatformerObject::load(pParams);

    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;
    dynamicBox.SetAsBox(m_width / 2.0f, m_height / 2.0f);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.filter.categoryBits = Box2D::ITEM;
    fixtureDef.filter.maskBits = Box2D::WALL | Box2D::PLAYER;
    m_pFixture = m_pBody->CreateFixture(&fixtureDef);


    m_pBody->SetFixedRotation(false);
    m_animations[IDLE] = new Animation("box idle", 1);
    m_animations[HIT] = new Animation("box hit", 2);

    m_curAnimation = IDLE;
    m_animations[m_curAnimation]->start();
}

void Box::update()
{
    PlatformerObject::update();
}
void Box::draw()
{
    PlatformerObject::draw();
}
void Box::collision() {}
void Box::clean() {}
