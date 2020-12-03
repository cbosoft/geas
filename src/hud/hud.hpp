#pragma once

#include "../transform/transform.hpp"
#include "../text/font/font.hpp"

class HUD : public Transform {
public:
    HUD(Transform *parent);

    Renderable *renderable() const override;

    void update() const;

private:
    Font font;
    Transform *hptext;
};