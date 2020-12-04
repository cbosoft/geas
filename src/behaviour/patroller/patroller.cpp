#include "patroller.hpp"

Patroller::Patroller(Actor *controlled)
    :   Behaviour(controlled)
    ,   dir(1)
{
    // do nothing
}