#include <chrono>

#include "hud.hpp"
#include "../game/game.hpp"
#include "../util/formatter.hpp"

void HUD::update() const
{
    auto *g = Game::singleton();
    auto *p = g->get_player();

    if (!p) {
        this->_text->disable();
        return;
    }
    else {
        this->_text->enable();
    }

    auto t1 = std::chrono::system_clock::now();
    auto dt = t1 - this->t0;
    int dt_ms = std::chrono::duration_cast<std::chrono::milliseconds>(dt).count();

    if (dt_ms > 500) {
        const Vec3 pos = p->absolute_position();
        std::string s = "hp: ";
        for (int i = 0; i < p->get_HP(); i++)
            s += "^";
        this->_text->set_text(s);
        this->t0 = t1;
    }

}