#include <iostream>
#include <ctime>

#include "window/window.hpp"
#include "globject/triangle.hpp"
#include "resourcemanager/resourcemanager.hpp"

int main(void)
{
  Window &w = window(640, 480, "geas");

  w.push_object(new GLTriangle({-0.5, -0.5}, {0.0, 0.5}, {0.5, -0.5}));
  w.run();
}
