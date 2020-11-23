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

    void update(unsigned int frame_number) const;
    void load_animations(const std::string &texture);

    void speed(float s);
    [[nodiscard]] float speed() const;

    void set_current_anim(const std::string &name);
    Animation *current_anim() const;
private:
    static const std::list<Animator *> &animators();

    unsigned int _inv_speed;
    void load_animations_json(json loops_obj);


    Animation *_current_anim;
    std::map<std::string, Animation *> animations;
};