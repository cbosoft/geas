#include <cstddef>

#include <GL/glew.h>

#include "../../../util/exception.hpp"
#include "../vertex/vertex.hpp"
#include "attrib_array.hpp"

AttribArray::AttribArray()
{
    constexpr unsigned int vsz = sizeof(GLVertex);

    glGenVertexArrays(1, &(this->_id));
    GL_ERROR_CHECK_DBG("AttribArray::ctor() -> after gen array");

    glBindVertexArray(this->_id);
    GL_ERROR_CHECK_DBG("AttribArray::ctor() -> after bind arr");

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vsz, (void *)offsetof(GLVertex, x));
    glEnableVertexAttribArray(0);
    GL_ERROR_CHECK_DBG("AttribArray::ctor() -> after enable position");

    // color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vsz, (void *)offsetof(GLVertex, r));
    GL_ERROR_CHECK_DBG(Formatter() << "AttribArray::ctor() -> after set color " << offsetof(GLVertex, r) << " " << vsz);
    glEnableVertexAttribArray(1);
    GL_ERROR_CHECK_DBG("AttribArray::ctor() -> after enable color");

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vsz, (void *)offsetof(GLVertex, s));
    glEnableVertexAttribArray(2);
    GL_ERROR_CHECK_DBG("AttribArray::ctor() -> after enable texture coords");
}

AttribArray::~AttribArray()
{
    // TODO delete
}

void AttribArray::use()
{
    glBindVertexArray(this->_id);
}