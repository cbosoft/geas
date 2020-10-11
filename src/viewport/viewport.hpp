#pragma once

#include "../vector/vector.hpp"

class Viewport {
  public:
    static Viewport& singleton();
    ~Viewport();

    Vec2 size; // viewport size relative to world
    Vec2 position; // viewport position in world coords
    Vec2 scale_world_to_view(Vec2);

  private:
    Viewport();
};
