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

    virtual void update();
    void physics_update();
    bool is_marked_for_destruction() const;
    void destroy();

    void reset_contact();
    void set_contact_bottom();
    void set_contact_top();
    void set_contact_left();
    void set_contact_right();
    bool get_contact_bottom() const;
    bool get_contact_top() const;
    bool get_contact_left() const;
    bool get_contact_right() const;

  private:
    GeasObject();
    Renderable *_renderable;
    bool _marked_for_destruction;

    unsigned int contact_mask;

};
