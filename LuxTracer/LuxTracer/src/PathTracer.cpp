#include <PathTracer.h>
#include <Math/mathUtils.h>
#include <iostream>

namespace lux
{
	math::vec3 PathTracer::GenerateRay(int x, int y, int imgWidth, int imgHeight, Camera const& cam)
	{
		math::vec3 finalColor{};

		//Handle MSAA
		for (int msaa{}; msaa < spp; ++msaa)
		{
			float u = (x + math::random_float()) / (imgWidth - 1);
			float v = (y + math::random_float()) / (imgHeight - 1);
			Ray ray = cam.GetRay(u, v);

			math::vec3 thruput{ 1.0f };
			math::vec3 ret{};

			for (int bounce{}; bounce <= maxBounce; ++bounce)
			{
				HitRecord rayPayload{};
				rayPayload.ray = ray;
				TraceRay(ray, 0.0f, math::inf, rayPayload);

				//Miss stop bounce
				if (!rayPayload.hasHit)
				{
					ret += rayPayload.color * thruput;
					break;
				}

				//Calculate next bounce
				ray.position = rayPayload.point + rayPayload.normal * 0.0001f;
				ray.direction = math::Normalize(rayPayload.normal + math::random_cos_weighted());
				ret += rayPayload.emission * thruput;
				thruput *= rayPayload.color;
			}

			finalColor += ret;
		}

		return finalColor * weightedSPP;
	}

	void PathTracer::TraceRay(Ray const& ray, float tMin, float tMax, HitRecord& rayPayload)
	{
		bool hasHit{};
		float closestT = tMax;

		for (int i{}, max{(int)scene->size()}; i < max; ++i)
		{
			if (IntersectionSphere(ray, (*scene)[i], tMin, closestT, rayPayload))
			{
				hasHit = true;
				closestT = rayPayload.t;
				rayPayload.goIndex = i;
			}
		}

		if (hasHit)
		{
			//Call closest hit
			ClosestHit(rayPayload);
		}

		else
		{
			//call miss
			Miss(rayPayload);
		}
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
		hitinfo.point = ray.At(root);
		hitinfo.normal = (hitinfo.point - go.position) / go.radius;
		return true;
	}

	void PathTracer::ClosestHit(HitRecord &hitInfo)
	{
		Material mat = scene[0][hitInfo.goIndex].mat;
		hitInfo.color = mat.color;
		hitInfo.emission = mat.emission * mat.emissionStr;
		hitInfo.hasHit = true;
	}

	void PathTracer::Miss(HitRecord &hitInfo)
	{
		//Draw gradient skybox
		math::vec3 dir = math::Normalize(hitInfo.ray.direction);
		float t = 0.5f * (dir.y + 1.0f);
		hitInfo.color = math::Lerp(math::vec3(1.0f), math::vec3(0.5f, 0.7f, 1.0f), t);
	}
}