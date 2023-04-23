#include <PathTracer.h>

namespace lux
{
	math::dvec3 PathTracer::GenerateRay(Ray const& ray, std::vector<GameObject> const& scene)
	{
		math::dvec3 finalColor{};

		for (int i{}; i < spp; ++i)
		{
			finalColor += TraceRay(ray, scene);
		}

		return finalColor * weightedSPP;
	}
	math::dvec3 PathTracer::TraceRay(Ray const& ray, std::vector<GameObject> const& scene)
	{
		for (const auto& go : scene)
		{
			double t = IntersectionSphere(ray, go);
			if (t > 0.0)
			{
				//Draw normals
				math::dvec3 normal = math::Normalize(ray.At(t) - math::dvec3(0.0, 0.0, -1.0));
				return 0.5 * math::dvec3(normal.x + 1.0, normal.y + 1.0, normal.z + 1.0);
			}
			else return Miss(ray);
		}
	}

	double PathTracer::IntersectionSphere(Ray const& ray, GameObject const& go)
	{
		math::dvec3 vec = ray.position - go.position;
		double a = math::Dot(ray.direction, ray.direction);
		double b = 2.0 * math::Dot(vec, ray.direction);
		double c = math::Dot(vec, vec) - go.radius * go.radius;
		double disc = b * b - 4 * a * c;
		if (disc < 0.0)
			return -1.0;
		else
		{
			return (-b - sqrt(disc)) / (2.0 * a);
		}
	}

	math::dvec3 PathTracer::ClosestHit()
	{
		return math::dvec3();
	}

	math::dvec3 PathTracer::Miss(Ray const& ray)
	{
		//Draw gradient skybox
		math::dvec3 dir = math::Normalize(ray.direction);
		double t = 0.5 * (dir.y + 1.0);
		return math::Lerp(math::dvec3(1.0), math::dvec3(0.5, 0.7, 1.0), t);
	}
}