#include "behaviour.hpp"
#include <list>

static std::list<Behaviour *> _behaviours;

Behaviour::Behaviour(Actor *controlled)
    :   _controlled(controlled)
{
    _behaviours.push_back(this);
}

void Behaviour::update_behaviours()
{
    for (auto &b : _behaviours) {
        b->update();
    }
}

Actor *Behaviour::controlled() const
{
    return this->_controlled;
}