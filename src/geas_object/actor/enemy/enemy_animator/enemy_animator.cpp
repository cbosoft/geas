#include "enemy_animator.hpp"

EnemyAnimator::EnemyAnimator(GeasObject &owner)
        : Animator(owner)
        , _horizontal_speed(0)
        , _on_ground(false)
{
    // do nothing
}
