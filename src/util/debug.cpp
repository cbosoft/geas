#include <iostream>

#include "debug.hpp"

void debug_msg(const std::string &s)
{
#ifdef DEBUG
  std::cerr << s << std::endl;
#else
  (void) s;
#endif
}
