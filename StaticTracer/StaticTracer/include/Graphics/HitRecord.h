#ifndef HITRECORD
#define HITRECORD

#include <Math/vec3.h>
#include <Graphics/Ray.h>

namespace pt
{
  class HitRecord
  {
  public:
    math::vec3 point;
    math::vec3 normal;
    float t;
    bool frontFace;

    inline void setFaceNormal(Ray const& ray, math::vec3 const& outwardNormal)
    {
      frontFace = (math::dot(ray.getDirection(), outwardNormal) < 0.0f);
      normal = frontFace ? outwardNormal : -outwardNormal;
    }
  };
}

#endif // !HITRECORD
