#include "geas_object.hpp"

GeasObject::GeasObject()
  :
    sprite(nullptr)
    , transform(nullptr)
    , _marked_for_destruction(false)
{
}

GeasObject::~GeasObject()
{

  if (sprite != nullptr) {
    delete this->sprite;
  }

  if (transform != nullptr) {
    delete this->transform;
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
