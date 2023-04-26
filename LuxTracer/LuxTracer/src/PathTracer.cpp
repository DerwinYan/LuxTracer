#include <PathTracer.h>
#include <Math/mathUtils.h>

namespace lux
{
	math::vec3 PathTracer::GenerateRay(int x, int y, int imgWidth, int imgHeight, Camera const& cam, std::vector<GameObject> const& _scene)
	{
		//scene = &_scene;
		math::vec3 finalColor{};

		for (int i{}; i < spp; ++i)
		{
			float u = (x + math::random_float()) / (imgWidth - 1);
			float v = (y + math::random_float()) / (imgHeight - 1);
			Ray ray = cam.GetRay(u, v);
			finalColor += TraceRay(ray, 0.0f, math::inf);
		}

		return finalColor * weightedSPP;
	}

	math::vec3 PathTracer::TraceRay(
		Ray const& ray, float tMin, float tMax
	)
	{
		bool anyHit = false;
		HitRecord finalHitInfo{};
		HitRecord hitinfo{};
		float closestT = tMax;

		for (int i{}, max{(int)scene->size()}; i < max; ++i)
		{
			if (IntersectionSphere(ray, (*scene)[i], tMin, closestT, hitinfo))
			{
				anyHit = true;
				closestT = hitinfo.t;
				finalHitInfo = hitinfo;
				finalHitInfo.goIndex = i;
			}
		}

		if (anyHit)
			return ClosestHit(finalHitInfo);
		else
			return Miss(ray);
	}

	bool PathTracer::IntersectionSphere(
		Ray const& ray, GameObject const& go, 
		float tMin, float tMax, HitRecord& hitinfo
	)
	{
		math::vec3 vec = ray.position - go.position;
		float a = math::LengthSq(ray.direction);
		float b = math::Dot(vec, ray.direction);
		float c = math::LengthSq(vec) - go.radius * go.radius;
		float disc = b*b - a*c;

		if (disc < 0.0f) 
			return false;

		float rootdisc = sqrt(disc);
		float root = (-b - rootdisc) / a;

		//Check both pos and neg root within t interval
		if (root < tMin || root > tMax)
		{
			root = (-b + rootdisc) / a;
			if (root < tMin || root > tMax)
				return false;
		}

		//Ray is within interval, calculate hitinfo
		hitinfo.t = root;
		//hitinfo.point = ray.At(root);
		//hitinfo.normal = (hitinfo.point - go.position) / go.radius;
		return true;
	}

	math::vec3 PathTracer::ClosestHit(HitRecord const& hitInfo)
	{
		//Draw normals
		//return 0.5f * (hitInfo.normal + math::vec3(1.0f, 1.0f, 1.0f));

		return scene[0][hitInfo.goIndex].mat.color;
	}

	math::vec3 PathTracer::Miss(Ray const& ray)
	{
		//Draw gradient skybox
		math::vec3 dir = math::Normalize(ray.direction);
		float t = 0.5f * (dir.y + 1.0f);
		return math::Lerp(math::vec3(1.0f), math::vec3(0.5f, 0.7f, 1.0f), t);
	}
}