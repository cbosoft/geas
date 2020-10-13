#pragma once

#include <map>

#include "../vector/vector.hpp"
#include "../image/image.hpp"

class Texture {

  public:
    friend class Window;
    Texture();

    static Texture *from_file(std::string filename);

    unsigned int get_id() const;
    void use();
    void request_animation_bounds(std::string name, unsigned int &lb, unsigned int &ub);
    float get_inv_n_frames();

  private:
    Texture(const ImageData &image);
    unsigned int texture_id;
    Vec2 offset, size;

    unsigned int n_animation_frames;
    std::map<std::string, std::pair<int, int>> animation_bounds_by_name;
};
