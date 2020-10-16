#include "geas_object.hpp"

GeasObject::GeasObject()
  :
    sprite(nullptr)
    , position(nullptr)
    , _marked_for_destruction(false)
{
}

GeasObject::~GeasObject()
{

  if (sprite != nullptr) {
    delete this->sprite;
  }

  if (position != nullptr) {
    delete this->position;
  }

  if (physics != nullptr) {
    delete this->physics;
  }
}

bool GeasObject::is_marked_for_destruction() const
{
  return this->_marked_for_destruction;
}

void GeasObject::destroy()
{
  this->_marked_for_destruction = true;
}
