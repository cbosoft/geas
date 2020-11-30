#pragma once

#include <list>
#include <map>
#include <string>

#include "../animation/animation.hpp"

class GeasObject;
class Animator {
public:

    friend class Game;
    GeasObject &owner;

    explicit Animator(GeasObject &owner);
    virtual ~Animator();

    virtual void load_animations(const std::string &texture);

    void update(unsigned int frame_number);

    void speed(float s);
    [[nodiscard]] float speed() const;

    void set_current_anim(const std::string &name);
    Animation *current_anim() const;

    unsigned int current_frame() const;

    void add_animation(Animation *anim);

private:
    static const std::list<Animator *> &animators();

    virtual void check_state() =0;
    void set_frame(unsigned int i) const;
    void load_animations_json(json loops_obj);


    Animation *_current_anim;
    std::map<std::string, Animation *> animations;


    unsigned int _inv_speed, _current_frame;
};