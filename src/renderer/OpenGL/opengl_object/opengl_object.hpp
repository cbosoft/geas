#pragma once

class OpenGLObject {
public:

    friend class BufferArray;
    friend class AttribArray;
    friend class Shader;
    friend class ShaderProgram;
    friend class ElementArray;

    inline unsigned int id() const
    {
        return this->_id;
    }

    virtual void use() =0;

private:

    unsigned int _id;

};