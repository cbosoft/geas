#pragma once

#include <string>
#include <map>

#include "../../../transform/transform.hpp"
#include "../../../util/json.hpp"
#include "../../../text/font/font.hpp"
#include "../ui_direction.hpp"

class UIElement : public Transform {
public:
    UIElement (Transform *parent, const Vec2 &position, const std::string &name, const Font &font, const std::string &text);

    UIElement *move(UIDirection dir);
    void set_direction(UIDirection dir, UIElement *dest);

    virtual void action() =0;

    [[nodiscard]] const std::string &get_name() const;

private:
    std::string name;
    std::map<UIDirection, UIElement *> targets;
    //Transform *selection_hint;
};