#include "geas_object.hpp"

GeasObject::GeasObject()
  :
    quad(nullptr)
    , position(nullptr)
    , _marked_for_destruction(false)
{
}

GeasObject::~GeasObject()
{

  if (quad != nullptr) {
    delete this->quad;
  }

  if (position != nullptr) {
    delete this->position;
  }

  // if (animator != nullptr) {
  //   delete this->animator;
  // }
  // if (animator != nullptr) {
  //   delete this->physics;
  // }
}

bool GeasObject::is_marked_for_destruction() const
{
  return this->_marked_for_destruction;
}

void GeasObject::destroy()
{
  this->_marked_for_destruction = true;
}
