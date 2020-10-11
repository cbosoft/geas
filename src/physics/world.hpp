#pragma once

#include "../vector/vector.hpp"

class World {

  public:

    ~World();

    static World &world();

    float get_time();


  private:

    World();

    float time;
    float time_scale;
};
