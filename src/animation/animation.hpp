#pragma once

#include <string>

#include "../util/json.hpp"

class Renderable;
class Animator;

class Animation {
public:
    Animation(const std::string &name, json j);

    bool interruptable() const;
    bool looping() const;
    bool ended(unsigned int at_frame) const;
    bool update(unsigned int current_frame, unsigned int &next_frame) const;

    const std::string &name() const;

private:

    unsigned int lb, ub;
    bool _interruptable, _looping;
    std::string _name;
};