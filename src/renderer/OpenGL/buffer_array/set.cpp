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
