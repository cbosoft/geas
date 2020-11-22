#pragma once

#include "../scene.hpp"

enum UIDirection {UIDir_Up, UIDir_Down, UIDir_Left, UIDir_Right};

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