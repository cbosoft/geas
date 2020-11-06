#include "material.hpp"

Material::Material(float elasticity, float friction)
    : _elasticity(elasticity)
    , _friction(friction)
{
    // do nothing
}

float Material::friction() const
{
    return this->_friction;
}

float Material::elasticity() const
{
    return this->_elasticity;
}
