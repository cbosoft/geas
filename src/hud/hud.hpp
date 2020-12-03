#pragma once

#include <chrono>

#include "../transform/transform.hpp"
#include "../text/font/font.hpp"
#include "../text/text/text.hpp"

class HUD : public Transform {
public:
    explicit HUD(Transform *parent);

    Renderable *renderable() const override;

    void update() const;

private:
    Text *_text;
    mutable std::chrono::time_point<std::chrono::system_clock> t0;
};