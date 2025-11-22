#include <Graphics/Sphere.h>
#include <Graphics/Ray.h>
#include <Graphics/HitRecord.h>

pt::Sphere::Sphere(math::vec3 const& center, float radius) : center{ center }, radius{ radius }
{}

bool pt::Sphere::hit(Ray const& ray, float tMin, float tMax, HitRecord& hitRecord) const
{
  // Point from vector: Q + t * vector
  // Sphere formula: 
  // [C-P]*[C-P} = r^2
  // [C- (Q+tv) ]*[C- (Q+tv) ] = r^2
  // {t^2 * v*v} + {-2tv(C-Q)} + {(C-Q)^2 - r^2} = 0
  //     a              b               c

  math::vec3 CQvec{ center - ray.getOrigin() };

  // Quadratic equation formula
  float a{ math::lengthSQ(ray.getDirection()) };
  float bPrime{ math::dot(ray.getDirection(), CQvec) };
  float c{ math::lengthSQ(CQvec) - radius * radius };

  float discriminant{ bPrime * bPrime - a * c };
  if (discriminant < 0.0f)
    return false;
  
  float sqrtDiscriminant{ std::sqrtf(discriminant) };
  float root{ (bPrime - sqrtDiscriminant) / a };
  if (root <= tMin || tMax <= root)
  {
    root = (bPrime + sqrtDiscriminant) / a;
    if (root <= tMin || tMax <= root)
      return false;
  }
  
  hitRecord.t = root;
  hitRecord.point = ray.at(hitRecord.t);
  math::vec3 outwardNormal{ (hitRecord.point - center) / radius };
  hitRecord.setFaceNormal(ray, outwardNormal);

  return true;
}
