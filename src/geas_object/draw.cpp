#include <iostream>
#include "geas_object.hpp"

void GeasObject::draw()
{
  this->update();

  if (this->quad != nullptr) {
    this->quad->draw();
  }
}
