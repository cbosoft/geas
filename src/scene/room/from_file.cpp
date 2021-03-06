#include <iostream>

#include "../../game/game.hpp"
#include "../../resourcemanager/resourcemanager.hpp"
#include "../../geas_object/tile/tile.hpp"
#include "../../geas_object/actor/enemy/enemy.hpp"
#include "../../tunnel/tunnel.hpp"
#include "room.hpp"


Room *Room::from_file(const std::string &path) {
    json room_spec = ResourceManager::singleton().get_metadata(path);
    return Room::from_json(room_spec);
}


Room *Room::from_json(const json &room_spec)
{
    std::string name = room_spec["name"];
    std::cerr << "Loading room \"" << name << "\"" << std::endl;
    auto *room = new Room(name);

    Vec2 bl, tr;

    for (json layer : room_spec["layers"]) {
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
        Transform *layer_transform = new Transform(room);
        std::string sname = layer["name"];
        room->layers[sname] = layer_transform;
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

    for (const auto &tunnel_spec : room_spec["tunnels"]) {
        std::string end = tunnel_spec["end"];
        std::string descriptor;
        auto tunit = tunnel_spec.find("descriptor");
        if (tunit != tunnel_spec.end()) {
            descriptor = *tunit;
        }
        std::string tag = Game::gen_tunnel_tag(room->name(), end, descriptor);

        std::string transition = "fade";
        tunit = tunnel_spec.find("transition");
        if (tunit != tunnel_spec.end()) {
            transition = *tunit;
        }

        auto pos_json = tunnel_spec["position"];
        Vec2 pos({pos_json[0], pos_json[1]});

        auto exit_offset_json = tunnel_spec["exit_offset"];
        Vec2 exit_offset({exit_offset_json[0], exit_offset_json[1]});

        room->tunnel_positions[tag] = pos + exit_offset;

        bool active = tunnel_spec["active"];
        if (active) {
            auto *tunnel = new Tunnel(room, end, descriptor, transition);
            tunnel->absolute_position(pos.promote(0.0f));
        }
    }

    // TODO get camera size from Camera
    const float camoff_x = 320.0f;
    const float camoff_y = 240.0f;
    auto it = room_spec.find("camera_bounds");
    if (it != room_spec.end()) {
        json bounds = *it;
        bl.x(bounds[0]);
        bl.y(bounds[1]);
        tr.x(bounds[2]);
        tr.y(bounds[3]);
    }
    Vec4 camera_area({bl.x() + camoff_x, bl.y()+camoff_y, tr.x() - bl.x() - camoff_x*2, tr.y() - bl.y() - camoff_y*2});
    room->set_camera_area(camera_area);

    it = room_spec.find("enemies");
    if (it != room_spec.end()) {
        for (const auto &enemy_spec : room_spec["enemies"]) {
            Enemy::from_spec(room, enemy_spec);
        }
    }
    return room;
}