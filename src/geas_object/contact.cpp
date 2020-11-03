#include "geas_object.hpp"

enum DIRENUM{none, BOTTOM, TOP, LEFT, RIGHT};

void GeasObject::reset_contact()
{
    this->contact_mask = 0;
}

void GeasObject::set_contact_bottom()
{
    this->contact_mask |= BOTTOM;
}

void GeasObject::set_contact_top()
{
    this->contact_mask |= TOP;
}

void GeasObject::set_contact_left()
{
    this->contact_mask |= LEFT;
}

void GeasObject::set_contact_right()
{
    this->contact_mask |= RIGHT;
}

bool GeasObject::get_contact_bottom() const
{
    return this->contact_mask & BOTTOM;
}

bool GeasObject::get_contact_top() const
{
    return this->contact_mask & TOP;
}

bool GeasObject::get_contact_left() const
{
    return this->contact_mask & LEFT;
}

bool GeasObject::get_contact_right() const
{
    return this->contact_mask & RIGHT;
}
