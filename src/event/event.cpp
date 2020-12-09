#include "event.hpp"

Event::Event()
    :   _should_delete(false)
{
    // do nothing
}

bool Event::should_delete() const
{
    return this->_should_delete;
}

void Event::should_delete(bool v)
{
    this->_should_delete = v;
}