#ifndef SCENE
#define SCENE

#include <Graphics/IHittable.h>
#include <memory>
#include <vector>
#include <Math/vec3.h>
namespace pt
{
  class Scene : public IHittable
  {
  public:
    void add(std::shared_ptr<IHittable> object);
    void clear();
    math::vec3 traceRay(Ray const& ray) const;

  private:
    bool hit(Ray const& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

  private:
    math::vec3 skyColor{0.5f, 0.7f, 1.0f};
    math::vec3 horizonColor{1.0f};

    std::vector<std::shared_ptr<IHittable>> objects;
  };
}

#endif // !SCENE
