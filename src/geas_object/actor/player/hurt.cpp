#include "player.hpp"

void Player::hurt(float v)
{
    this->HP -= v;

    //auto *anim = (PlayerAnimator *)this->animator();
    //anim->hurt();
    //if (this->is_dead()) {
        //anim->dead();
    //}
}