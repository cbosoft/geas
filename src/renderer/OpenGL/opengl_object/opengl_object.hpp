#pragma once

class OpenGLObject {
public:

    friend class BufferArray;
    friend class Shader;
    friend class ShaderProgram;

    inline unsigned int id() const
    {
        return this->_id;
    }

    virtual void use() =0;

private:

    unsigned int _id;

};