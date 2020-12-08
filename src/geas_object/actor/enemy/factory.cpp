#include "../../../util/exception.hpp"
#include "enemy.hpp"
#include "hedgehog/hedgehog.hpp"

Enemy *Enemy::from_spec(Transform *parent, const json &spec)
{
    // spec defines the enemy type and all that

    std::string enemy_type = spec["type"];
    json pos_spec = spec["position"];
    Vec3 pos({pos_spec[0], pos_spec[1], 0.0f});

    Enemy *rv = nullptr;
    if (enemy_type == "hedgehog") {
        rv = new Hedgehog(parent);
    }

    if (!rv)
        throw Exception("SpecError", "Enemy spec not understood.");

    rv->absolute_position(pos);

    return rv;
}