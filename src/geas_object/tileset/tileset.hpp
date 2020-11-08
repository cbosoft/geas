#pragma once

#include <list>
#include <string>

#include "../../util/json.hpp"
#include "../../vector/vector.hpp"
#include "../../transform/transform.hpp"

void create_tiles(Transform *parent, json tile_data);
void create_tile(Transform *parent, json tile_data);
void create_tile(Transform *parent, unsigned int variant, const Vec2 &position, float size, const std::string &texture_path);
void create_tile(Transform *parent, unsigned int variant, const Vec3 &position, float size, const std::string &texture_path);
