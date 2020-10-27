#include <GL/glew.h>

#include "../glerror.hpp"
#include "buffer_array.hpp"

BufferArray::BufferArray()
    : _invalid(true)
{
    glGenBuffers(1, &this->_id);
    gl_error_check("BufferArray::ctor()");
}

BufferArray::BufferArray(BufferArray &&other)
{
    // move constructor: move id from other to this.
    this->_id = other._id;
}

BufferArray::~BufferArray()
{
    // TODO: teardown array
}

std::size_t BufferArray::size() const
{
    return this->_vertices.size();
}
