#include "camera_animator.hpp"

CameraAnimator::CameraAnimator(GeasObject &owner)
    :   Animator(owner)
    ,   forwards(true)
    ,   paused(false)
{
    // do nothing
}