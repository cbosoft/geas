#pragma once
#include <array>

template<typename T, unsigned int N>
class VectorN {

  public:
    VectorN()
      : VectorN(std::array<T, N>())
    {
      // do nothing
    }
    VectorN(std::array<T, N> data)
    {
      for (unsigned int i = 0; i < N; i++) {
        this->data[i] = data[i];
      }
    }
    ~VectorN() {};

    T get(int i) const
    {
      return this->data[i];
    }

    void set(int i, T value)
    {
      this->data[i] = value;
    }

  private:

    std::array<T, N> data;
};

//typedef VectorN<float, 2> Vec2;

class Vec2 : public VectorN<float, 2> {

  public:
    Vec2(float x, float y) : VectorN({x,y}) { }

    float x() const
    {
      return this->get(0);
    }

    void x(float value)
    {
      this->set(0, value);
    }

    float y() const
    {
      return this->get(1);
    }

    void y(float value)
    {
      this->set(1, value);
    }
};

class Vec3 : public VectorN<float, 3> {
  public:
    Vec3(float x, float y, float z) : VectorN({x,y,z}) { }

    float x() const
    {
      return this->get(0);
    }

    void x(float value)
    {
      this->set(0, value);
    }

    float y() const
    {
      return this->get(1);
    }

    void y(float value)
    {
      this->set(1, value);
    }

    float z() const
    {
      return this->get(2);
    }

    void z(float value)
    {
      this->set(2, value);
    }
};
