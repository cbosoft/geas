#pragma once

#include <list>
//#include "../geas_object/geas_object.hpp"

class GeasObject;
class Animator {
public:

    friend class Game;
    GeasObject &owner;

    explicit Animator(GeasObject &owner);
    virtual ~Animator();

    void update(unsigned int frame_number) const;

    void speed(float s);
    [[nodiscard]] float speed() const;

private:
    static const std::list<Animator *> &animators();
    virtual void state_changed() =0;

    unsigned int _inv_speed;
};