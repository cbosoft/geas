#include "animated_tile.hpp"
#include "tile_animator/tile_animator.hpp"

AnimatedTile::AnimatedTile(Transform *parent, float s, const std::string &texture_path)
    :   Tile(parent, s, texture_path)
{
    auto *a = new TileAnimator(*this);
    a->load_animations(texture_path);
    this->animator(a);
}


AnimatedTile::AnimatedTile(Transform *parent, float s, const std::string &texture_path, Vec4 collider)
        :   Tile(parent, s, texture_path, collider)
{
    auto *a = new TileAnimator(*this);
    a->load_animations(texture_path);
    this->animator(a);
}
