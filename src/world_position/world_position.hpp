#pragma once

#include "../vector/vector.hpp"

// position in world coordinates
class WorldPosition {

  public:
    WorldPosition(float x, float y, float z);
    WorldPosition(Vec3 position);

    Vec3 in_window_coords() const;

  private:
    Vec3 position;

};
