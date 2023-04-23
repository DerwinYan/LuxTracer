#pragma once

#include <Math/dvec3.h>
#include <Ray.h>
#include <GameObject.h>
#include <Camera.h>

namespace lux
{
	struct PathTracer
	{
		struct HitRecord
		{
			math::dvec3 point{};
			math::dvec3 normal{};
			double t{};
		};

		PathTracer(int samplesPerPixel = 1) : spp{ samplesPerPixel }, weightedSPP{ 1.0 / spp } {}
		void SetSamples(int sample)
		{
			spp = sample;
			weightedSPP = 1.0 / spp;
		}

		/*
			TraceRay will generate X rays
			Ray goes through BVH and test intersection with spheres
			Hit info will be generated and closest hit will be updated
			On miss, if there was a hit shade according to material, else shade skybox
		*/

		//math::dvec3 GenerateRay(Ray const& ray, std::vector<GameObject> const& scene);
		math::dvec3 GenerateRay(int x, int y, int imgWidth, int imgHeight, Camera const& cam, std::vector<GameObject> const& scene);
		math::dvec3 TraceRay(Ray const& ray, std::vector<GameObject> const& scene, double tMin, double tMax);
		bool IntersectionSphere(Ray const& ray, GameObject const& sphere, double tMin, double tMax, HitRecord &hitinfo);
		math::dvec3 ClosestHit(HitRecord const& hitInfo);
		math::dvec3 Miss(Ray const& ray);

		int spp{ 1 };

	private:
		double weightedSPP{ 1.0 };
	};
}