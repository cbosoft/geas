#include "attack_animation.hpp"

void AttackAnimation::enable_hitbox() const
{
    auto *hitbox = this->owner.get_melee_hitbox();
    if (hitbox) {
        hitbox->enable();
    }
}

void AttackAnimation::disable_hitbox() const
{
    auto *hitbox = this->owner.get_melee_hitbox();
    if (hitbox) {
        hitbox->disable();
    }
}

void AttackAnimation::position_hitbox() const
{
    auto *hitbox = this->owner.get_melee_hitbox();
    if (hitbox) {
        auto *rect = hitbox->get_collider();
        Vec3 position = this->positions[this->i].promote(0.0f);
        rect->relative_position(position);
    }
}