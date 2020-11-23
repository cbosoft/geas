#include "animator.hpp"
#include "../animation/animation.hpp"
#include "../geas_object/geas_object.hpp"
#include "../resourcemanager/resourcemanager.hpp"

static std::list<Animator *> _animators;

Animator::Animator(GeasObject &owner)
    : owner(owner)
    , _current_anim(nullptr)
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

void Animator::update(unsigned int frame_number)
{
    if (frame_number % this->_inv_speed == 0) {

        if (this->_current_anim) {
            // get next frame index from animation
            if (this->_current_anim->update(this->_current_frame, this->_current_frame)) {
                this->set_frame(this->_current_frame); // set new frame for rendering
            }
            else {
                // the animation is no longer valid; update the state and try again
                this->check_state();
                this->update(frame_number);
                return;
            }
        }

    }
}


void Animator::set_frame(unsigned int i) const
{
    auto *r = this->owner.renderable();
    if (r) {
        r->current_frame(i);
    }
}


void Animator::set_current_anim(const std::string &name)
{
    this->_current_anim = this->animations[name];
}


Animation *Animator::current_anim() const
{
    return this->_current_anim;
}

unsigned int Animator::current_frame() const
{
    return this->_current_frame;
}

void Animator::load_animations(const std::string &texture)
{
    // TODO: don't read in the file, load it from cache
    // TODO: cache animations

    json j = ResourceManager::singleton().get_metadata(texture);

    for (const auto &[key, value] : j.items()) {
        std::string skey = key;
        if (key == "animation_loops") {
            this->load_animations_json(value);
        }
    }
}

void Animator::load_animations_json(json loops_obj)
{
    for (const auto &[key, value] : loops_obj.items()) {
        std::string name = key;
        auto *a = new Animation(name, value);
        this->animations[name] = a;
    }
}