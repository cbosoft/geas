#include "geas_object.hpp"

static const unsigned int BOTTOM = (1 << 1);
static const unsigned int TOP = (1 << 2);
static const unsigned int LEFT = (1 << 3);
static const unsigned int RIGHT = (1 << 4);

void GeasObject::contact_bottom(bool v)
{
    if (v) {
        this->contact_mask |= BOTTOM;
    }
    else {
        this->contact_mask &= ~BOTTOM;
    }
}

void GeasObject::contact_top(bool v)
{
    if (v) {
        this->contact_mask |= TOP;
    }
    else {
        this->contact_mask &= ~TOP;
    }
}

void GeasObject::contact_left(bool v)
{
    if (v) {
        this->contact_mask |= LEFT;
    }
    else {
        this->contact_mask &= ~LEFT;
    }
}

void GeasObject::contact_right(bool v)
{
    if (v) {
        this->contact_mask |= RIGHT;
    }
    else {
        this->contact_mask &= ~RIGHT;
    }
}

bool GeasObject::contact_bottom() const
{
    return this->contact_mask & BOTTOM;
}

bool GeasObject::contact_top() const
{
    return this->contact_mask & TOP;
}

bool GeasObject::contact_left() const
{
    return this->contact_mask & LEFT;
}

bool GeasObject::contact_right() const
{
    return this->contact_mask & RIGHT;
}
