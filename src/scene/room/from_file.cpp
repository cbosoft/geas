#include <iostream>

#include "../resourcemanager/resourcemanager.hpp"
#include "../geas_object/tile/tile.hpp"
#include "scene.hpp"

Scene *Scene::from_file(const std::string &path)
{
    json scene_spec = ResourceManager::singleton().get_json(path);

    std::string name = scene_spec["name"];
    std::cerr << "Loading scene \"" << name << "\"" << std::endl;
    auto *scene = new Scene(name);

    Vec2 bl, tr;

    for (json layer : scene_spec["layers"]) {
        std::string tileset_path = layer["tileset"];
        json tileset_meta = ResourceManager::singleton().get_metadata(tileset_path);
        json collision_information;
        auto it = tileset_meta.find("collision");
        if (it != tileset_meta.end()) {
            collision_information = *it;
        }

        json tileset_named_colliders = tileset_meta["named_colliders"];

        bool collision_override = false, collision_override_value = false;
        it = layer.find("collision");
        if (it != layer.end()) {
            collision_override = true;
            collision_override_value = *it;
        }

        unsigned int tile_layer = 0;
        it = layer.find("tile_layer");
        if (it != layer.end()) {
            tile_layer = *it;
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

            if (y > tr.y())
                tr.y(y);

            if (y < bl.y())
                bl.y(y);

            for (const auto &cell : row) {

                if (x > tr.x())
                    tr.x(x);

                if (x < bl.x())
                    bl.x(x);

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
                    else if (info.is_string()) {
                        std::string collider_name = info;
                        auto rectinfo = tileset_named_colliders[collider_name];
                        rect.set(0, float(rectinfo["x"])*s);
                        rect.set(1, float(rectinfo["y"])*s);
                        rect.set(2, float(rectinfo["w"])*s);
                        rect.set(3, float(rectinfo["h"])*s);
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
                    t->set_variant(tile_layer, variant);
                    Vec3 pos({x, y, 0.0f}); // TODO z ordering
                    t->absolute_position(pos);
                }
                x += s;
            }
        }

    }

    const float camoff = 240.0f;
    Vec4 camera_area({bl.x() + camoff, bl.y()+camoff, tr.x() - bl.x() - camoff*2, tr.y() - bl.y() - camoff*2});
    scene->set_camera_area(camera_area);
    scene->camera()->absolute_position(Vec3({0.0f, 128.0f, 0.0f}));
    return scene;
}