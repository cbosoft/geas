#pragma once

#include <vector>

#include "../../../vector/vector.hpp"
#include "../vertex/vertex.hpp"
#include "../opengl_object/opengl_object.hpp"
#include "../attrib_array/attrib_array.hpp"

class BufferArray final : public OpenGLObject {
public:
    BufferArray();
    ~BufferArray();
    BufferArray(const BufferArray &other) =delete; // no copying
    BufferArray(BufferArray &&other);

    void set(int i, const GLVertex &vertex);
    void set(int i, const Vec3 &position);
    void set(int i, const Vec4 &colour);
    void set(int i, const Vec2 &texture);

    void add(const GLVertex &vertex);
    void add(const Vec3 &position, const Vec4 &colour, const Vec2 &texture);
    void add(const Vec3 &position, const Vec2 &texture);
    void add(const Vec3 &position, const Vec4 &colour);
    void add(const Vec3 &position);
    std::size_t size() const;

    void use() override;


private:
    void sync();

    std::vector<GLVertex> _vertices;
    bool _invalid;
    AttribArray *attribArray;
};