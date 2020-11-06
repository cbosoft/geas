#include "material.hpp"

Material *Material::get_default()
{
    static Material default_material{0.1, 1.0};
    return &default_material;
}