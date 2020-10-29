#pragma once

#include <vector>

#include "../opengl_object/opengl_object.hpp"

class ElementArray final : OpenGLObject {
public:
    ElementArray();
    ~ElementArray();

    void use() override;
    void add(unsigned int index);
    void set(unsigned int i, unsigned int value);
    std::size_t size() const;

private:

    void sync();

    bool _invalid;
    std::vector<unsigned int> _indices;
};