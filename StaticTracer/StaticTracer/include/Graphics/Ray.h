#ifndef RAY
#define RAY

#include <Math/vec3.h>

namespace pt
{
  class Ray
  {
    Ray(math::vec3 const& origin, math::vec3 const& direction) : origin{ origin }, direction{ direction } {}
    math::vec3 const& getOrigin() const noexcept { return origin; }
    math::vec3 const& getDirection() const noexcept { return direction; }
    math::vec3 at(float t) const { return origin + t * direction; }

  private:
    math::vec3 origin;
    math::vec3 direction;
  };
}

#endif // !RAY
