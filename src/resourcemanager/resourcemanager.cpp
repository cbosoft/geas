#include <fstream>
#include <sstream>

#include "../util/exception.hpp"
#include "resourcemanager.hpp"

ResourceManager::ResourceManager()
{
    // initialise: open necessary files
    get_shader("shaders/block_colour_frag.glsl");
    get_shader("shaders/textured_frag.glsl");
    get_shader("shaders/simple_vert.glsl");
}

ResourceManager::~ResourceManager()
{
    // do nothing?
}

std::string ResourceManager::read_text_file(std::string filename)
{
  // TODO: abstract away filesystem
  std::ifstream ifs(filename);

  if (!ifs) {
    throw IOError(Formatter() << "Could not read file \"" << filename << "\"");
  }

  std::string s;
  std::stringstream ss;

  while (std::getline(ifs, s)) {
    ss << s << "\n";
  }

  return ss.str();
}
