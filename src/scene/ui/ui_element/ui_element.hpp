#pragma once

#include <string>
#include <map>

#include "../../../transform/transform.hpp"
#include "../../../util/json.hpp"
#include "../../../util/font/font.hpp"
#include "../ui_direction.hpp"

class UIElement : public Transform {
public:
    UIElement (Transform *parent, const std::string &name, json j, const Font &font);
    std::string move(UIDirection dir);

private:
    std::string name;
    std::map<UIDirection, std::string> targets;
    //Transform *selection_hint;
};