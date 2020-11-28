#pragma once

#include <map>

#include "../../../vector/vector.hpp"
#include "../../../util/image/image.hpp"

class Texture {

  public:
    static Texture *from_file(const std::string &path);
    explicit Texture(const ImageData &image);
    void use() const;
    [[nodiscard]] Vec4 get_rect(unsigned int l, unsigned int i) const;
    [[nodiscard]] Vec4 get_rect(unsigned int l, unsigned int r, unsigned int c) const;

  private:
    unsigned int glid;
    unsigned int _number_frames_x, _number_frames_y, _number_layers;
    float framewidth, frameheight;
};
