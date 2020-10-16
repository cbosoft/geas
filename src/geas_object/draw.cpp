#include <iostream>
#include "geas_object.hpp"

void GeasObject::draw()
{
  this->update();

  if (this->sprite != nullptr) {
    this->sprite->draw();
  }

}
