#include <iostream>

#include "../resourcemanager/resourcemanager.hpp"
#include "../geas_object/tile/tile.hpp"
#include "scene.hpp"

Scene *Scene::from_file(const std::string &path)
{
    auto *scene = new Scene();
    json scene_spec = ResourceManager::singleton().get_json(path);

    std::string name = scene_spec["name"];
    std::cerr << "Loading scene \"" << name << "\"" << std::endl;

    for (const auto& layer : scene_spec["layers"]) {
        std::string tileset_path = layer["tileset"];
        const float s = layer["size"];
        const float x_offset = static_cast<float>(layer["x_offset"])*s;
        const float y_offset = static_cast<float>(layer["y_offset"])*s;

        float h = static_cast<float>(layer["tiles"].size())*s;
        float y = h + y_offset, x;
        for (const auto &row : layer["tiles"]) {
            x = x_offset;
            y -= s;
            for (const auto &cell : row) {
                int i = cell;
                if (i) {
                    int variant = i-1;
                    auto *t = new Tile(scene, s, tileset_path, true, true);
                    t->renderable()->set_frame(variant);
                    Vec3 pos({x, y, 0.0f}); // TODO z ordering
                    t->absolute_position(pos);
                }
                x += s;
            }
        }

    }

    return scene;
}