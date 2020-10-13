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

    VectorN<T,N+1> promote(T fill)
    {
      VectorN<T,N+1> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i));
      }
      rv.set(N, fill);
      return rv;
    }

    VectorN<T,N-1> demote()
    {
      VectorN<T,N+1> rv;
      for (unsigned int i = 0; i < N-1; i++) {
        rv.set(i, this->get(i));
      }
      return rv;
    }

    VectorN<T,N> operator+(const VectorN<T,N> &rhs)
    {
      VectorN<T,N> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i)+rhs.get(i));
      }
      return rv;
    }

    VectorN<T,N> operator-(const VectorN<T,N> &rhs)
    {
      VectorN<T,N> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i)-rhs.get(i));
      }
      return rv;
    }

    VectorN<T,N> operator*(const VectorN<T,N> &rhs)
    {
      VectorN<T,N> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i)*rhs.get(i));
      }
      return rv;
    }

    VectorN<T,N> operator/(const VectorN<T,N> &rhs)
    {
      VectorN<T,N> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i)/rhs.get(i));
      }
      return rv;
    }

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

    float r() const
    {
      return this->get(0);
    }

    void r(float value)
    {
      this->set(0, value);
    }

    float g() const
    {
      return this->get(1);
    }

    void g(float value)
    {
      this->set(1, value);
    }

    float b() const
    {
      return this->get(2);
    }

    void b(float value)
    {
      this->set(2, value);
    }

    float a() const
    {
      return this->get(3);
    }

    void a(float value)
    {
      this->set(3, value);
    }

  private:

    std::array<T, N> data;
};

typedef VectorN<float, 2> Vec2;
typedef VectorN<float, 3> Vec3;
typedef VectorN<float, 4> Vec4;
