#include <iostream>

#include "ui_element.hpp"
#include "../../../geas_object/tile/tile.hpp"
#include "../../../util/font/font.hpp"

UIElement::UIElement(Transform *parent, const std::string &iname, json j, const Font &font)
    :   Transform(parent)
    ,   name(iname)
{
    json position = j["position"];
    this->relative_position(Vec3({position[0], position[1], 0.0f}));
    std::string text = j["text"];
    font.render_text(this, text);

    json directions = j["directions"];
    for (const auto &[dirjson, namejson] : directions.items()) {
        std::string sdir = dirjson, sname = namejson;
        if (sdir == "up") {
            this->targets[UIDir_Up] = sname;
        }
        else if (sdir == "down") {
            this->targets[UIDir_Down] = sname;
        }
        else if (sdir == "left") {
            this->targets[UIDir_Left] = sname;
        }
        else if (sdir == "right") {
            this->targets[UIDir_Right] = sname;
        }
    }

}

std::string UIElement::move(UIDirection dir)
{
    auto it = this->targets.find(dir);
    if (it != this->targets.end()) {
        return it->second;
    }
    return this->name;
}
