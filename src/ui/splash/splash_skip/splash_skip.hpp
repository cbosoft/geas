#pragma once

#include "../../ui_element/ui_element.hpp"
#include "../splash_transit/splash_transit.hpp"

class SplashSkip : public UIElement {
public:
    SplashSkip(Transform *parent, SplashTransit *event);

    void action() override;

private:
    SplashTransit *_event;
};