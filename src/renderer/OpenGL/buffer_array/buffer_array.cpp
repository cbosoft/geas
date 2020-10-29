#include <GL/glew.h>

#include "../glerror.hpp"
#include "buffer_array.hpp"

BufferArray::BufferArray()
    : _invalid(true)
    , attribArray(nullptr)
{
    glGenBuffers(1, &this->_id);
    gl_error_check("BufferArray::ctor()");

    glBindBuffer(GL_ARRAY_BUFFER, this->_id);
    this->attribArray = new AttribArray();
}

BufferArray::BufferArray(BufferArray &&other)
{
    // move constructor: move id from other to this.
    this->_id = other._id;
}

BufferArray::~BufferArray()
{
    // TODO: teardown array and attrib
}

std::size_t BufferArray::size() const
{
    return this->_vertices.size();
}
