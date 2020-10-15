#pragma once
// vim: foldmethod=marker

#include <array>
#include <cmath>

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
    VectorN(T fill)
    {
      for (unsigned int i = 0; i < N; i++) {
        this->data[i] = fill;
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

    VectorN<T,N+1> promote(T fill) const
    {
      VectorN<T,N+1> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i));
      }
      rv.set(N, fill);
      return rv;
    }

    VectorN<T,N-1> demote() const
    {
      VectorN<T,N-1> rv;
      for (unsigned int i = 0; i < N-1; i++) {
        rv.set(i, this->get(i));
      }
      return rv;
    }

    // arithmetic operators {{{

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

    VectorN<T,N> operator+(T other)
    {
      VectorN<T,N> rhs(other);
      VectorN<T,N> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i)+rhs.get(i));
      }
      return rv;
    }

    VectorN<T,N> operator-(T other)
    {
      VectorN<T,N> rhs(other);
      VectorN<T,N> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i)-rhs.get(i));
      }
      return rv;
    }

    VectorN<T,N> operator*(T other)
    {
      VectorN<T,N> rhs(other);
      VectorN<T,N> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i)*rhs.get(i));
      }
      return rv;
    }

    VectorN<T,N> operator/(T other)
    {
      VectorN<T,N> rhs(other);
      VectorN<T,N> rv;
      for (unsigned int i = 0; i < N; i++) {
        rv.set(i, this->get(i)/rhs.get(i));
      }
      return rv;
    }

    // }}}
    // named accessors {{{

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
    // }}}
    // vector maths {{{

    T square_magnitude() const
    {
      T rv = 0.0;
      for (unsigned int i = 0; i < N; i++) {
        rv += data[i]*data[i];
      }
      return rv;
    }

    T magnitude() const
    {
      return std::pow(square_magnitude(), 0.5);
    }

    T dot(const VectorN<T, N> &rhs)
    {
      T rv = 0.0;
      for (unsigned int i = 0; i < N; i++) {
        rv = this->data[i]*rhs.data[i];
      }
      return rv;
    }

    // }}}


  private:

    std::array<T, N> data;
};

// more arithmetic {{{
template<typename T, unsigned int N>
VectorN<T,N> operator+(float f, const VectorN<T, N>& rhs)
{
  return rhs+f;
}

template<typename T, unsigned int N>
VectorN<T,N> operator-(float f, const VectorN<T, N>& rhs)
{
  VectorN<T,N> lhs(f);
  return lhs - rhs;
}

  template<typename T, unsigned int N>
VectorN<T,N> operator*(float f, const VectorN<T, N>& rhs)
{
  return rhs*f;
}

  template<typename T, unsigned int N>
VectorN<T,N> operator/(float f, const VectorN<T, N>& rhs)
{
  VectorN<T,N> lhs(f);
  return lhs/rhs;
}
// }}}

typedef VectorN<float, 2> Vec2;
typedef VectorN<float, 3> Vec3;
typedef VectorN<float, 4> Vec4;
