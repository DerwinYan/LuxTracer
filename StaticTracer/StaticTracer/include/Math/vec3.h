#ifndef VEC3
#define VEC3

#include <iostream>

namespace math
{
  union vec3
  {
    float data[3];
    struct { float x, y, z; };
    struct { float r, g, b; };

    inline vec3() : data{ 0.0f, 0.0f, 0.0f } {}
    inline vec3(float val) : data{ val, val, val } {}
    inline vec3(float x, float y, float z) : data{ x, y, z } {}
    inline vec3(vec3 const& rhs) : x{ rhs.x }, y{ rhs.y }, z{ rhs.z } {}
    inline vec3& operator=(vec3 const& rhs)
    {
      if (this == &rhs) return *this;
      x = rhs.x; y = rhs.y; z = rhs.z;
      return *this;
    }
    inline vec3 const operator-() const noexcept { return vec3(-x, -y, -z); }
    inline vec3& operator+=(vec3 const& rhs) noexcept
    {
      x += rhs.x; y += rhs.y; z += rhs.z;
      return *this;
    }
    inline vec3& operator*=(float scalar) noexcept
    {
      x *= scalar; y *= scalar; z *= scalar;
      return *this;
    }
    inline vec3& operator/=(float scalar) { return *this *= 1.0f / scalar; }
  };

  inline float lengthSQ(vec3 const& v) noexcept { return v.x * v.x + v.y * v.y + v.z * v.z; }
  inline float length(vec3 const& v) noexcept { return std::sqrtf(lengthSQ(v)); }
  inline vec3 operator+(vec3 const& lhs, vec3 const& rhs) noexcept { return vec3{ lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z }; }
  inline vec3 operator-(vec3 const& lhs, vec3 const& rhs) noexcept { return vec3{ lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z }; }
  inline vec3 operator*(vec3 const& v, float scalar) noexcept { return vec3{ v.x * scalar, v.y * scalar, v.z * scalar }; }
  inline vec3 operator*(float scalar, vec3 const& v) noexcept { return vec3{ v.x * scalar, v.y * scalar, v.z * scalar }; }
  inline vec3 operator/(vec3 const& v, float scalar) noexcept { return v * (1 / scalar); }
  inline vec3 operator/(float scalar, vec3 const& v) noexcept { return v * (1 / scalar); }
  inline vec3 normalize(vec3 const& v) noexcept { return v / length(v); }
  inline float dot(vec3 const& lhs, vec3 const& rhs) noexcept { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
  inline vec3 cross(vec3 const& lhs, vec3 const& rhs) noexcept
  {
    return vec3
    {
      lhs.y * rhs.z - lhs.z * rhs.y,
      lhs.z * rhs.x - lhs.x * rhs.z,
      lhs.x * rhs.y - lhs.y * rhs.x
    };
  }
  inline std::ostream& operator<<(std::ostream& os, vec3 const& v) { return os << v.x << ", " << v.y << ", " << v.z << '\n'; }
}

#endif // !VEC3
