#include "physics.hpp"

void Physics::add_constraint(bitmask_t mask)
{
    this->direction_constraints_mask &= mask;
}

void Physics::add_constraint(DirectionalConstraint constraint)
{
    this->add_constraint(static_cast<bitmask_t>(constraint));
}

void Physics::remove_constraint(bitmask_t mask)
{
    this->direction_constraints_mask &= ~mask;
}

void Physics::remove_constraint(DirectionalConstraint constraint)
{
    this->remove_constraint(static_cast<bitmask_t>(constraint));
}

bool Physics::check_constraint(bitmask_t mask) const
{
    return (mask & this->direction_constraints_mask);
}

bool Physics::check_constraint(DirectionalConstraint constraint) const
{
    return this->check_constraint(static_cast<bitmask_t>(constraint));
}
