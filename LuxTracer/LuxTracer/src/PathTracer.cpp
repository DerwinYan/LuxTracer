#include <PathTracer.h>
#include <Math/mathUtils.h>

namespace lux
{
	math::dvec3 PathTracer::GenerateRay(Ray const& ray, std::vector<GameObject> const& scene)
	{
		math::dvec3 finalColor{};

		for (int i{}; i < spp; ++i)
		{
			finalColor += TraceRay(ray, scene, 0.0, math::inf);
		}

		return finalColor * weightedSPP;
	}
	math::dvec3 PathTracer::TraceRay(
		Ray const& ray, std::vector<GameObject> const& scene, 
		double tMin, double tMax
	)
	{
		bool anyHit = false;
		HitRecord finalHitInfo{};
		HitRecord hitinfo{};
		double closestT = tMax;

		for (const auto& go : scene)
		{
			if (IntersectionSphere(ray, go, tMin, tMax, hitinfo))
			{
				anyHit = true;
				closestT = hitinfo.t;
				finalHitInfo = hitinfo;
			}
		}

		if (anyHit)
			return ClosestHit(finalHitInfo);
		else
			return Miss(ray);
	}

	bool PathTracer::IntersectionSphere(
		Ray const& ray, GameObject const& go, 
		double tMin, double tMax, HitRecord& hitinfo
	)
	{
		math::dvec3 vec = ray.position - go.position;
		double a = math::LengthSq(ray.direction);
		double b = math::Dot(vec, ray.direction);
		double c = math::LengthSq(vec) - go.radius * go.radius;
		double disc = b*b - a*c;

		if (disc < 0.0) 
			return false;

		double rootdisc = sqrt(disc);
		double root = (-b - rootdisc) / a;

		//Check both pos and neg root within t interval
		if (root < tMin || root > tMax)
		{
			root = (-b + rootdisc) / a;
			if (root < tMin || root > tMax)
				return false;
		}

		//Ray is within interval, calculate hitinfo
		hitinfo.t = root;
		hitinfo.point = ray.At(root);
		hitinfo.normal = (hitinfo.point - go.position) / go.radius;
		return true;
	}

	math::dvec3 PathTracer::ClosestHit(HitRecord const& hitInfo)
	{
		//Draw normals
		return 0.5 * (hitInfo.normal + math::dvec3(1.0, 1.0, 1.0));
	}

	math::dvec3 PathTracer::Miss(Ray const& ray)
	{
		//Draw gradient skybox
		math::dvec3 dir = math::Normalize(ray.direction);
		double t = 0.5 * (dir.y + 1.0);
		return math::Lerp(math::dvec3(1.0), math::dvec3(0.5, 0.7, 1.0), t);
	}
}