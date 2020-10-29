#include "../../../util/exception.hpp"
#include "element_array.hpp"

#include <GL/glew.h>

ElementArray::ElementArray()
    : _invalid(true)
{
    glGenBuffers(1, &this->_id);
}

ElementArray::~ElementArray()
{
    // teardown
}

void ElementArray::use()
{
    if (this->_invalid)
        this->sync();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id);
}

void ElementArray::sync()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices.size()*sizeof(unsigned int), &(this->_indices[0]), GL_STATIC_DRAW);
    this->_invalid = false;
}

void ElementArray::add(unsigned int index)
{
    this->_indices.push_back(index);
    this->_invalid = true;
}

void ElementArray::set(unsigned int i, unsigned int value)
{
    if (i >= this->size())
        throw OutOfRange(Formatter() << "ElementArray::set(i, value) got index out of range. Index " << i << " too big for vector of size " << this->size() );

    this->_indices[i] = value;
    this->_invalid = true;
}

std::size_t ElementArray::size() const
{
    return this->_indices.size();
}