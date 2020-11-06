#pragma once

#include <map>

#include "../../../vector/vector.hpp"
#include "../../../util/image/image.hpp"

class Texture {

  public:
    static Texture *from_file(const std::string &path);
    Texture(const ImageData &image);
    void use() const;

  private:
    unsigned int glid;
};
