#include "buffer_array.hpp"

void BufferArray::add(const GLVertex &vertex)
{
    this->_vertices.push_back(vertex);
    this->_effective_size ++;
    this->_invalid = true;
}

void BufferArray::add(const Vec3& position, const Vec4 &colour, const Vec2 &texture)
{
    this->_vertices.push_back({
        position.x(), position.y(), position.z(),
        colour.r(), colour.g(), colour.b(), colour.a(),
        texture.x(), texture.y()});
    this->_effective_size ++;
    this->_invalid = true;
}

void BufferArray::add(const Vec3 &position, const Vec2 &texture)
{
    this->_vertices.push_back({
        position.x(), position.y(), position.z(),
        1.0f, 1.0f, 1.0f, 1.0f,
        texture.x(), texture.y()});
    this->_effective_size ++;
    this->_invalid = true;
}

void BufferArray::add(const Vec3& position, const Vec4 &colour)
{
    this->_vertices.push_back({
        position.x(), position.y(), position.z(),
        colour.r(), colour.g(), colour.b(), colour.a(),
        0.0f, 0.0f});
    this->_effective_size ++;
    this->_invalid = true;
}

void BufferArray::add(const Vec3 &position)
{
    this->_vertices.push_back({
        position.x(), position.y(), position.z(),
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f});
    this->_effective_size ++;
    this->_invalid = true;
}
