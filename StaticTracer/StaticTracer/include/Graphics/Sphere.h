#ifndef SPHERE
#define SPHERE

#include <Graphics/IHittable.h>
#include <Math/vec3.h>

namespace pt
{
  class Ray;
  class HitRecord;

  class Sphere : public IHittable
  {
  public:
    Sphere(math::vec3 const& center, float radius);
    virtual bool hit(Ray const& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

  private:
    math::vec3 center;
    float radius;
  };
}

#endif // !SPHERE
