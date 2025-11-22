#include <Graphics/Scene.h>
#include <Graphics/HitRecord.h>
#include <Common.h>
#include <Graphics/Ray.h>

void pt::Scene::add(std::shared_ptr<IHittable> object)
{
  objects.emplace_back(object);
}

void pt::Scene::clear()
{
  objects.clear();
}

math::vec3 pt::Scene::traceRay(Ray const& ray) const
{
  HitRecord hitRecord{};
  if (hit(ray, 0.001f, utils::infinity, hitRecord))
  {
    // map range from [-1,1] to [0,1] to visualize normals
    return 0.5f * (hitRecord.normal + math::vec3{1.0f});
  }

  // Return skybox color
  float t{ 0.5f * (math::normalize(ray.getDirection()).y + 1.0f) };
  return math::lerp(skyColor, horizonColor, 1.0f - t);
}

bool pt::Scene::hit(Ray const& ray, float tMin, float tMax, HitRecord& hitRecord) const
{
  HitRecord tempRecord;
  bool anyHit{};
  float closestHit{tMax};

  for (auto const& object : objects)
  {
    if (object->hit(ray, tMin, closestHit, tempRecord))
    {
      anyHit = true;
      closestHit = tempRecord.t;
      hitRecord = tempRecord;
    }
  }

  return anyHit;
}
