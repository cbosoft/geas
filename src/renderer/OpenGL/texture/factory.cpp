#include <map>

#include "texture.hpp"


Texture *Texture::from_file(const std::string &path)
{
    static std::map<std::string, Texture *> _texture_cache;
    auto it = _texture_cache.find(path);
    if (it != _texture_cache.end()) {
        return it->second;
    }

    ImageData im(path);
    auto *t = new Texture(im);
    _texture_cache[path] = t;
    return t;
}