#pragma once

#include <vector>
#include <mutex>

#include "../../../vector/vector.hpp"
#include "../vertex/vertex.hpp"
#include "../opengl_object/opengl_object.hpp"

class BufferArray final : public OpenGLObject {
public:
    BufferArray();
    ~BufferArray();
    BufferArray(const BufferArray &other) =delete; // no copying
    BufferArray(BufferArray &&other);

    void set(int i, const Vertex &vertex);
    void set(int i, const Vec3 &position);
    void set(int i, const Vec4 &colour);
    void set(int i, const Vec2 &texture);

    void add(const Vertex &vertex);
    void add(const Vec3 &position, const Vec4 &colour, const Vec2 &texture);
    void add(const Vec3 &position, const Vec2 &texture);
    void add(const Vec3 &position, const Vec4 &colour);
    void add(const Vec3 &position);
    std::size_t size() const;

    void use() override;


private:
    void sync();

    typedef std::lock_guard<std::mutex> lock_guard;
    std::mutex mutex;
    std::vector<Vertex> _vertices;
    bool _invalid;
};