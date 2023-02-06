#ifndef EMENY_H
#define EMENY_H

#include "PlatformerObject.h"
class Enemy : public PlatformerObject {
  public:
    virtual std::string type() { return "Enemy"; }
    virtual void draw() { PlatformerObject::draw(); }
    virtual void update() { PlatformerObject::update(); }

  protected:
    int m_health;
    Enemy() : PlatformerObject(){};
};

#endif
