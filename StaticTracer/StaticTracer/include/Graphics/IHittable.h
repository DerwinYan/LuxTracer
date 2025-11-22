#ifndef IHITTABLE
#define IHITTABLE

namespace pt
{
  class Ray;

  class IHittable
  {
  public:
    virtual ~IHittable() = default;
    virtual bool hit(Ray const& ray, float tMin, float tMax, class HitRecord& record) const = 0;
  };
}

#endif // !IHITTABLE
