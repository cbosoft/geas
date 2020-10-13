#include <iostream>
#include <ctime>

#include "window/window.hpp"
#include "globject/quad.hpp"
#include "resourcemanager/resourcemanager.hpp"

int main(void)
{
  Window &w = window(640, 480, "geas");

  Quad *quad1 = Quad::square(2.0);
  quad1->update_texture("textures/bg.png");
  w.push_object(quad1);

  Quad *quad2 = Quad::square(0.3);
  quad2->update_position(Vec3({0.0, 0.9, 0.0}));
  quad2->update_texture("textures/sprite_sheet.png");
  quad2->set_loop("run");
  w.push_object(quad2);

  w.run();
}
