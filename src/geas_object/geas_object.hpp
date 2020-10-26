#pragma once

#include "../globject/sprite.hpp"
#include "../transform/transform.hpp"
#include "../physics/physics.hpp"

// TODO: rename to simply "Object"
class GeasObject : public Transform {

  public:
    Sprite *sprite;
    Physics *physics;

    GeasObject(Transform *parent);
    virtual ~GeasObject();

    virtual void update() =0;
    void physics_update();
    void draw();
    bool is_marked_for_destruction() const;
    void destroy();

  private:
    GeasObject();
    bool _marked_for_destruction;

};
