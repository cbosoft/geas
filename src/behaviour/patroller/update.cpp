#include "patroller.hpp"

void Patroller::update()
{
    Actor *a = this->controlled();

    if (a->contact_right())
        dir = -1;

    if (a->contact_left())
        dir = 1;

    //if (!a->contact_bottom())
    //    dir = 0;

    a->move(dir);

}