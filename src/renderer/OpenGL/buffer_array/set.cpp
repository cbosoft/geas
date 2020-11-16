#include "../../../util/exception.hpp"

#include "buffer_array.hpp"

void BufferArray::set(unsigned int i, const GLVertex &vertex)
{
    if (i > this->size())
        throw OutOfRange(Formatter() << "Index " << i << " out of range for bufferarray of size " << this->size());
    else if (i == this->size())
        this->add(vertex);
    else {
        // copy vertex into array
        GLVertex v = this->_vertices[i];

        this->_vertices[i] = vertex;

        if (v != this->_vertices[i])
            this->_invalid = true;
    }
}

void BufferArray::set(unsigned int i, const Vec3 &position)
{
    if (i > this->size())
        throw OutOfRange(Formatter() << "Index " << i << " out of range for bufferarray of size " << this->size());
    else if (i == this->size())
        this->add(position);
    else {

        GLVertex v = this->_vertices[i];

        this->_vertices[i].x = position.x();
        this->_vertices[i].y = position.y();
        this->_vertices[i].z = position.z();

        if (v != this->_vertices[i])
            this->_invalid = true;
    }

    if (this->_effective_size <= i) {
        this->_effective_size = i+1;
    }
}

void BufferArray::set(unsigned int i, const Vec4 &colour)
{
    if (i > this->size())
        throw OutOfRange(Formatter() << "Index " << i << " out of range for bufferarray of size " << this->size());

    GLVertex v = this->_vertices[i];

    this->_vertices[i].r = colour.r();
    this->_vertices[i].g = colour.g();
    this->_vertices[i].b = colour.b();
    this->_vertices[i].a = colour.a();

    if (v != this->_vertices[i])
        this->_invalid = true;

    if (this->_effective_size <= i) {
        this->_effective_size = i+1;
    }
}

void BufferArray::set(unsigned int i, const Vec2 &texture)
{
    if (i > this->size())
        throw OutOfRange(Formatter() << "Index " << i << " out of range for bufferarray of size " << this->size());

    GLVertex v = this->_vertices[i];

    this->_vertices[i].s = texture.x();
    this->_vertices[i].t = texture.y();

    if (v != this->_vertices[i])
        this->_invalid = true;

    if (this->_effective_size <= i) {
        this->_effective_size = i+1;
    }
}


void BufferArray::set_monochrome_rect_centred(const Vec3 &centre, const Vec2 &size, const Vec4 &colour)
{
    const float hsx = size.x()*0.5f;
    const float hsy = size.y()*0.5f;
    const float cx = centre.x();
    const float cy = centre.y();
    const float cz = centre.z();

    const float r = colour.r();
    const float g = colour.g();
    const float b = colour.b();
    const float a = colour.a();

    GLVertex verts[4] = {
            {hsx + cx, hsy + cy, cz, r, g, b, a, 1.0f, 1.0f},
            {hsx + cx, -hsy + cy, cz, r, g, b, a, 1.0f, 0.0f},
            {-hsx + cx, -hsy + cy, cz, r, g, b, a, 0.0f, 0.0f},
            {-hsx + cx, hsy + cy, cz, r, g, b, a, 0.0f, 1.0f}
    };

    for (int i = 0; i < 4; i++) {
        this->set(i, verts[i]);
    }
}

void BufferArray::set_textured_rect_centred(const Vec3 &centre, const Vec2 &size, const Vec4 &colour, const Vec4 &rect, const Vec2 &scale)
{
    const float hsx = size.x()*0.5f;
    const float hsy = size.y()*0.5f;
    const float cx = centre.x();
    const float cy = centre.y();
    const float cz = centre.z();

    const float r = colour.r();
    const float g = colour.g();
    const float b = colour.b();
    const float a = colour.a();

    const float tx = rect.get(0);
    const float ty = rect.get(1);
    const float tw = rect.get(2);
    const float th = rect.get(3);

    const float thw = tw*0.5f;
    const float thh = th*0.5f;
    const float tcx = tx + thw;
    const float tcy = ty + thh;

    const float sx = scale.x()*thw;
    const float sy = scale.y()*thh;

    GLVertex verts[4] = {
            {hsx + cx, hsy + cy, cz, r, g, b, a, tcx + sx, tcy + sy},
            {hsx + cx, -hsy + cy, cz, r, g, b, a, tcx + sx, tcy - sy},
            {-hsx + cx, -hsy + cy, cz, r, g, b, a, tcx - sx, tcy - sy},
            {-hsx + cx, hsy + cy, cz, r, g, b, a, tcx - sx, tcy + sy}
    };

    for (int i = 0; i < 4; i++) {
        this->set(i, verts[i]);
    }
}
