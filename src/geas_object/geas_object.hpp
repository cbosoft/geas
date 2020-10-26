#pragma once

#include "../transform/transform.hpp"
#include "../physics/physics.hpp"
#include "../renderable/renderable.hpp"

// TODO: rename to simply "Object"
class GeasObject : public Transform {

  public:
    Physics *physics;

    GeasObject(Transform *parent);
    virtual ~GeasObject();

    [[nodiscard]] Renderable *renderable() const override;
    void renderable(Renderable *);

    virtual void update() =0;
    void physics_update();
    bool is_marked_for_destruction() const;
    void destroy();

  private:
    GeasObject();
    Renderable *_renderable;
    bool _marked_for_destruction;

};
