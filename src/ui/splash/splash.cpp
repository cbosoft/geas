#include "../../game/game.hpp"
#include "../../geas_object/tile/animated_tile/animated_tile.hpp"
#include "splash_transit/splash_transit.hpp"
#include "splash_skip/splash_skip.hpp"
#include "splash.hpp"

SplashScreen::SplashScreen()
    :   UI("splash")
{
    auto *background = new AnimatedTile(this, Vec2({640.0f, 480.0f}), "assets/splash/engine_splash.png");
    background->relative_position(Vec3({-320,-240,0}));

    auto *selector = new Transform(this);
    this->set_selection_hint(selector);

    auto *transit = new SplashTransit("main_menu", 3);
    auto *game = Game::singleton();
    game->push_event(transit);

    auto *skip = new SplashSkip(this, transit);
    this->select(skip);

}