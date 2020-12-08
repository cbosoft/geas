#pragma once

#include "../enemy.hpp"

class Hedgehog : public Enemy {
public:
    Hedgehog(Transform *parent);

    void update() override;
};