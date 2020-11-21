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

    for (json layer : scene_spec["layers"]) {
        std::string tileset_path = layer["tileset"];
        json tileset_meta = ResourceManager::singleton().get_metadata(tileset_path);
        json collision_information;
        auto it = tileset_meta.find("collision");
        if (it != tileset_meta.end()) {
            collision_information = *it;
        }

        bool collision_override = false, collision_override_value = false;
        it = layer.find("collision");
        if (it != layer.end()) {
            collision_override = true;
            collision_override_value = *it;
        }

        const float s = layer["size"];
        const float x_offset = static_cast<float>(layer["x_offset"])*s;
        const float y_offset = static_cast<float>(layer["y_offset"])*s;

        float h = static_cast<float>(layer["tiles"].size())*s;
        float y = h + y_offset, x;
        Transform *layer_transform = new Transform(scene);
        std::string sname = layer["name"];
        scene->layers[sname] = layer_transform;
        for (const auto &row : layer["tiles"]) {
            x = x_offset;
            y -= s;
            for (const auto &cell : row) {
                int i = cell;
                if (i) {
                    int variant = i-1;

                    json info;
                    try {
                        info = collision_information[variant];
                    }
                    catch (std::exception) {

                    }

                    Vec4 rect({0.0f, 0.0f, s,s});
                    bool collider = true;
                    if (info.is_object()) {
                        rect.set(0, float(info["x"])*s);
                        rect.set(1, float(info["y"])*s);
                        rect.set(2, float(info["w"])*s);
                        rect.set(3, float(info["h"])*s);
                    }
                    else if (info.is_boolean()) {
                        collider = info;
                    }
                    else {
                        std::cerr << "collision information not understood: ignoring." << std::endl;
                    }

                    if (collision_override)
                        collider = collision_override_value;

                    Tile *t = nullptr;
                    if (collider) {
                        t = new Tile(layer_transform, s, tileset_path, rect);
                    }
                    else {
                        t = new Tile(layer_transform, s, tileset_path);
                    }
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