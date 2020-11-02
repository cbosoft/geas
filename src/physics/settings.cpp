#include "physics.hpp"

static float _global_gravity_scale = 3e-5;
float Physics::global_gravity_scale()
{
    return _global_gravity_scale;
}

void Physics::global_gravity_scale(float v)
{
    _global_gravity_scale = v;
}


static int _update_period_us = 500;
int Physics::update_period_us()
{
    return _update_period_us;
}

void Physics::update_period_us(int v)
{
    _update_period_us = v;
}

void Physics::update_rate_hz(int v)
{
    _update_period_us = 1000000/v;
}

static float _time_scale = 1.0f;
float Physics::time_scale()
{
    return _time_scale;
}

void Physics::time_scale(float v)
{
    _time_scale = v;
}