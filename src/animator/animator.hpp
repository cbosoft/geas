#pragma once

#include <list>


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

    unsigned int _inv_speed;
};