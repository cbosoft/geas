#include "player_animator.hpp"

PlayerAnimator::PlayerAnimator(GeasObject &owner)
    : Animator(owner)
    , _horizontal_speed(0)
    , _on_ground(false)
{
    // do nothing
}