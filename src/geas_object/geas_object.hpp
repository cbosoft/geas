#pragma once

#include "../globject/quad.hpp"
#include "../world_position/world_position.hpp"
#include "../physics/physics.hpp"

class GeasObject {

  public:
    Quad *quad;
    WorldPosition *position;
    Physics *physics;

    GeasObject();
    virtual ~GeasObject();

    virtual void update() =0;
    void physics_update();
    void draw();
    bool is_marked_for_destruction() const;
    void destroy();

  private:
    bool _marked_for_destruction;

};
