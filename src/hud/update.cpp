#include <chrono>

#include "hud.hpp"
#include "../game/game.hpp"
#include "../util/formatter.hpp"

void HUD::update() const
{
    auto *g = Game::singleton();
    auto *p = g->get_player();
    (void) p;

    auto t1 = std::chrono::system_clock::now();
    auto dt = t1 - this->t0;
    int dt_ms = std::chrono::duration_cast<std::chrono::milliseconds>(dt).count();

    if (dt_ms > 500) {
        const Vec3 pos = p->absolute_position();
        std::string s = "hp: ";
        for (int i = 0; i < 3; i++)
            s += "o";
        this->_text->set_text(s);
        this->t0 = t1;
    }

}