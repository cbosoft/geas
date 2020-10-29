#include <GL/glew.h>

#include "../vertex/vertex.hpp"
#include "attrib_array.hpp"

AttribArray::AttribArray()
{
    constexpr unsigned int vsz = sizeof(GLVertex);

    glGenVertexArrays(1, &(this->_id));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vsz, 0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vsz, (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vsz, (void *)(7*sizeof(float)));
    glEnableVertexAttribArray(2);
}

AttribArray::~AttribArray()
{
    // TODO delete
}

void AttribArray::use()
{
    glBindVertexArray(this->_id);
}