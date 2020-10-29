#pragma once

typedef struct GLVertex {
    float x;
    float y;
    float z;

    float r;
    float g;
    float b;
    float a;

    float s;
    float t;

    bool operator==(const GLVertex &other) const
    {
        return (
                (this->x == other.x) &&
                (this->x == other.x) &&
                (this->y == other.y) &&
                (this->z == other.z) &&

                (this->r == other.r) &&
                (this->g == other.g) &&
                (this->b == other.b) &&
                (this->a == other.a) &&

                (this->s == other.s) &&
                (this->t == other.t)
                );
    }

    bool operator!=(const GLVertex &other) const
    {
        return !((*this) == other);
    }
} GLVertex;
