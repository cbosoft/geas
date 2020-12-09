#include "splash_skip.hpp"

SplashSkip::SplashSkip(Transform *parent, SplashTransit *event)
    :   UIElement(parent, Vec2(0.0f), "skip", "assets/fonts/vict.png", "")
    ,   _event(event)
{

}