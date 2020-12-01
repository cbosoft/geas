#include "animation.hpp"

bool Animation::update(unsigned int current_frame, unsigned int &next_frame)
{
    if (this->ended(current_frame))
        return false;

    next_frame = current_frame + 1;
    if ((next_frame >= this->ub) || (next_frame < this->lb))
        next_frame = this->lb;

    return true;
}