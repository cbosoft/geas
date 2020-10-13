#pragma once

#include "../image/image.hpp"

class Texture {

  public:
    Texture();

    static Texture *from_file(std::string filename);

    unsigned int get_id();
    void use();

  private:
    Texture(const ImageData &image);
    unsigned int texture_id;
};
