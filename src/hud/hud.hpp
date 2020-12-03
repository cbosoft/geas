#pragma once

#include "../transform/transform.hpp"
#include "../text/font/font.hpp"
#include "../text/text/text.hpp"

class HUD : public Transform {
public:
    HUD(Transform *parent);

    Renderable *renderable() const override;

    void update() const;

private:
    Text *_text;
};