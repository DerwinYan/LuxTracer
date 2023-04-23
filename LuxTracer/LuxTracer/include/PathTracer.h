#pragma once

#include <Math/dvec3.h>
#include <Ray.h>
#include <GameObject.h>

namespace lux
{
	struct PathTracer
	{
		PathTracer(int samplesPerPixel = 1) : spp{ samplesPerPixel }, weightedSPP{ 1.0 / spp } {}

		/*
			TraceRay will generate X rays
			Ray goes through BVH and test intersection with spheres
			Hit info will be generated and closest hit will be updated
			On miss, if there was a hit shade according to material, else shade skybox
		*/

		math::dvec3 GenerateRay(Ray const& ray, std::vector<GameObject> const& scene);
		math::dvec3 TraceRay(Ray const& ray, std::vector<GameObject> const& scene);
		double IntersectionSphere(Ray const& ray, GameObject const& sphere);
		math::dvec3 ClosestHit();
		math::dvec3 Miss(Ray const& ray);

		int spp{ 1 };

	private:
		double weightedSPP{ 1.0 };
	};
}