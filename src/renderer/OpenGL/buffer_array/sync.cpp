#include <GL/glew.h>

#include "../glerror.hpp"
#include "buffer_array.hpp"

void BufferArray::sync()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->_id);
    glBufferData(GL_ARRAY_BUFFER, this->_effective_size * sizeof(GLVertex), &(this->_vertices[0]), GL_STATIC_DRAW);
    gl_error_check("BufferArray::sync()");
    this->_invalid = true;
}
