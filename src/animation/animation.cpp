#include "animation.hpp"

Animation::Animation(const std::string &name, json j)
    : lb(0)
    , ub(1)
    , _interruptable(true)
    , _looping(true)
    , _name(name)
{
    if (j.is_object()) {
        for (const auto &[key, value] : j.items()) {
            std::string skey = key;
            if (key == "lb") {
                lb = value;
            }
            else if (key == "ub") {
                ub = value;
            }
            else if (key == "interruptable") {
                _interruptable = value;
            }
            else if (key == "looping") {
                _looping = value;
            }
            else {
                // unknown key -> TODO: exception
            }
        }
    }
    else if (j.is_array()) {
        lb = j[0];
        ub = j[1];
    }
    else {
        // j is malformed -> TODO: exception
    }
}

bool Animation::interruptable() const { return this->_interruptable; }
bool Animation::looping() const { return this->_looping; }
const std::string &Animation::name() const { return this->_name; }
bool Animation::ended(unsigned int at_frame) const { return (!this->_looping) && (this->ub-1 <= at_frame); }
