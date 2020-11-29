#pragma once

#include "../scene.hpp"

#include "ui_direction.hpp"

class UI : public Scene {
public:

    static UI *from_json(nlohmann::json j);

    void move(UIDirection dir);
    void accept();
    void cancel();

    bool is_ui() override { return false; }

private:
    UI();
};