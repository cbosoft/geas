#pragma once

#include "../opengl_object/opengl_object.hpp"

class AttribArray : public OpenGLObject {
public:

    AttribArray();
    ~AttribArray();

    void use() override;

};