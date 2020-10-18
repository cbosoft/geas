#include "geas_object.hpp"

GeasObject::GeasObject()
  : Transform()
    , sprite(nullptr)
    , _marked_for_destruction(false)
{
    // do nothing
}

GeasObject::GeasObject(Transform *parent)
  : Transform(parent)
  , sprite(nullptr)
  , _marked_for_destruction(false)
{
    // do nothing
}

GeasObject::~GeasObject()
{

  if (sprite != nullptr) {
    delete this->sprite;
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
