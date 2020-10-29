#include "buffer_array.hpp"

void BufferArray::set(int i, const GLVertex &vertex)
{
    // copy vertex into array
    GLVertex v = this->_vertices[i];

    this->_vertices[i] = vertex;

    if (v != this->_vertices[i])
        this->_invalid = true;
}

void BufferArray::set(int i, const Vec3 &position)
{
    GLVertex v = this->_vertices[i];

    this->_vertices[i].x = position.x();
    this->_vertices[i].y = position.y();
    this->_vertices[i].z = position.z();

    if (v != this->_vertices[i])
        this->_invalid = true;
}

void BufferArray::set(int i, const Vec4 &colour)
{
    GLVertex v = this->_vertices[i];

    this->_vertices[i].r = colour.r();
    this->_vertices[i].g = colour.g();
    this->_vertices[i].b = colour.b();
    this->_vertices[i].a = colour.a();

    if (v != this->_vertices[i])
        this->_invalid = true;
}

void BufferArray::set(int i, const Vec2 &texture)
{
    GLVertex v = this->_vertices[i];

    this->_vertices[i].s = texture.x();
    this->_vertices[i].t = texture.y();

    if (v != this->_vertices[i])
        this->_invalid = true;
}


void BufferArray::set_monochrome_rect_centred(const Vec3 &centre, const Vec2 &size, const Vec4 &colour)
{
    const float hsx = size.x()*0.5f;
    const float hsy = size.y()*0.5f;
    const float cx = centre.x();
    const float cy = centre.y();
    const float cz = centre.z();

    const float r = colour.r();
    const float g = colour.g();
    const float b = colour.b();
    const float a = colour.a();

    GLVertex verts[4] = {
            {hsx + cx, hsy + cy, cz, r, g, b, a, 0.0f, 0.0f},
            {hsx + cx, -hsy + cy, cz, r, g, b, a, 0.0f, 0.0f},
            {-hsx + cx, -hsy + cy, cz, r, g, b, a, 0.0f, 0.0f},
            {-hsx + cx, hsy + cy, cz, r, g, b, a, 0.0f, 0.0f}
    };

    for (int i = 0; i < 4; i++) {
        this->set(i, verts[i]);
    }
}