#pragma once

#include "../geas_object/geas_object.hpp"

class Player final : public GeasObject {
  public:
    Player();

    void update() override;

};
