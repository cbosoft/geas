#pragma once

class Material final {
public:
    Material(float elasticity, float friction);
    ~Material() =default;

    float elasticity() const;
    float friction() const;

    static Material *get_default();

private:
    float _elasticity;
    float _friction;
};