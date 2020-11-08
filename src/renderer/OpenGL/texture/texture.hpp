#pragma once

#include <map>

#include "../../../vector/vector.hpp"
#include "../../../util/image/image.hpp"

class Texture {

  public:
    static Texture *from_file(const std::string &path);
    Texture(const ImageData &image);
    void use() const;
    Vec4 get_rect(unsigned int i) const;

  private:
    unsigned int glid;
    unsigned int _number_frames;
    float framewidth;
};
