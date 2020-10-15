#pragma once

#include "../vector/vector.hpp"

// position in world coordinates
class WorldPosition {

  public:
    WorldPosition(float x, float y, float z);
    WorldPosition(Vec3 position);

    Vec3 vec() const;
    Vec3 in_window_coords() const;

    void set(Vec2 other);
    void set(Vec3 other);

    WorldPosition &operator+=(const Vec2& other)
    {
      this->position = this->position + other.promote(0.0);
      return *this;
    }

  private:
    Vec3 position;

};
