#include <iostream>
#include "../tile/tile.hpp"
#include "tileset.hpp"

void create_tiles(Transform *parent, json tile_data)
{
    for (auto it : tile_data) {
        create_tile(parent, it);
    }
}

void create_tile(Transform *parent, json tile_data)
{
    unsigned int variant = tile_data["variant"];
    float x = tile_data["x"];
    float y = tile_data["y"];
    Vec2 position({x, y});
    float size = 32.0f;
    std::string texture_path = tile_data["sprite_sheet"];

    std::cerr << "adding tile from sheet" << texture_path << std::endl;
    create_tile(parent, variant, position, size, texture_path);
}

void create_tile(Transform *parent, unsigned int variant, const Vec2 &position, float size, const std::string &texture_path)
{
    create_tile(parent, variant, position.promote(0.0f), size, texture_path);
}

void create_tile(Transform *parent, unsigned int variant, const Vec3 &position, float size, const std::string &texture_path)
{
    auto *t = new Tile(parent, size, texture_path, true, true);
    auto *r = t->renderable();
    r->set_frame(variant);
    t->absolute_position(position.promote(0.0f));
}
