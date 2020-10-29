#include <GL/glew.h>

#include "../glerror.hpp"
#include "buffer_array.hpp"

void BufferArray::use()
{
    if (this->_invalid)
        this->sync();

    glBindBuffer(GL_ARRAY_BUFFER, this->_id);
    gl_error_check("BufferArray::use()");
}
