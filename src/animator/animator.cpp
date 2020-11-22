#include "animator.hpp"
#include "../geas_object/geas_object.hpp"

static std::list<Animator *> _animators;

Animator::Animator(GeasObject &owner)
    : owner(owner)
    , _inv_speed(1)
{
    _animators.push_back(this);
}

Animator::~Animator()
{
    _animators.remove(this);
}

const std::list<Animator *> &Animator::animators()
{
    return _animators;
}

void Animator::speed(float speed)
{
    float invfspeed = 1.0f/speed;
    this->_inv_speed = static_cast<unsigned int>(invfspeed);
}

float Animator::speed() const
{
    auto invfspeed = static_cast<float>(this->_inv_speed);
    float speed = 1.0f/invfspeed;
    return speed;
}

void Animator::update(unsigned int frame_number) const
{
    if (frame_number % this->_inv_speed == 0) {
        Renderable *renderable = this->owner.renderable();
        if (renderable) {
            renderable->increment_frame();
        }
    }
}