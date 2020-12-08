#include "event.hpp"

bool Event::should_delete() const
{
    return this->_should_delete;
}

void Event::should_delete(bool v)
{
    this->_should_delete = v;
}