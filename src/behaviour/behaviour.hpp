#pragma once

#include "../geas_object/actor/actor.hpp"

class Behaviour {
public:
    Behaviour(Actor *controlled);
    virtual ~Behaviour() =default;

    static void update_behaviours();

    Actor *controlled() const;

private:

    virtual void update() =0;

    Actor *_controlled;
};