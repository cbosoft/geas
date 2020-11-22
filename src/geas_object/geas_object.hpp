#pragma once

#include "../transform/transform.hpp"
#include "../physics/physics.hpp"
#include "../renderable/renderable.hpp"
#include "../animator/animator.hpp"

// TODO: rename to simply "Object"
class GeasObject : public Transform {

  public:
    Physics *physics;

    GeasObject(Transform *parent);
    virtual ~GeasObject();

    [[nodiscard]] Renderable *renderable() const override;
    void renderable(Renderable *);

    [[nodiscard]] Animator *animator() const;
    void animator(Animator *animator);

    virtual void update();
    bool is_marked_for_destruction() const;
    void destroy();

    void contact_bottom(bool v);
    void contact_top(bool v);
    void contact_left(bool v);
    void contact_right(bool v);
    bool contact_bottom() const;
    bool contact_top() const;
    bool contact_left() const;
    bool contact_right() const;

  private:
    GeasObject();
    Renderable *_renderable;
    Animator *_animator;
    bool _marked_for_destruction;

    unsigned int contact_mask;

};
