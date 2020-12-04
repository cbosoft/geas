#pragma once

#include "../behaviour.hpp"

class Patroller : public Behaviour {
public:
    Patroller(Actor *controlled);

private:

    void update() override;

    int dir;
};