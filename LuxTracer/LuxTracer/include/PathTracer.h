#pragma once

#include <Math/vec3.h>
#include <Ray.h>
#include <GameObject.h>
#include <Camera.h>

namespace lux
{
	struct PathTracer
	{
		struct HitRecord
		{
			math::vec3 point{};
			math::vec3 normal{};
			float t{};
			int goIndex;
		};

		PathTracer(int samplesPerPixel = 1, int numBounce = 1) 
			: spp{ samplesPerPixel }, weightedSPP{ 1.0f / spp }, maxBounce{ numBounce } {}

		void SetSamples(int sample)
		{
			spp = sample;
			weightedSPP = 1.0f / spp;
		}

		void SetBounce(int numBounce)
		{
			maxBounce = numBounce;
		}

		void LinkScene(std::vector<GameObject> const& _scene)
		{
			scene = &_scene;
		}

		/*
			TraceRay will generate X rays
			Ray goes through BVH and test intersection with spheres
			Hit info will be generated and closest hit will be updated
			On miss, if there was a hit shade according to material, else shade skybox
		*/

		math::vec3 GenerateRay(int x, int y, int imgWidth, int imgHeight, Camera const& cam, std::vector<GameObject> const& scene);
		math::vec3 TraceRay(Ray const& ray, float tMin, float tMax);
		bool IntersectionSphere(Ray const& ray, GameObject const& sphere, float tMin, float tMax, HitRecord &hitinfo);
		math::vec3 ClosestHit(HitRecord const& hitInfo);
		math::vec3 Miss(Ray const& ray);


	private:
		int spp{ 1 };
		float weightedSPP{ 1.0 };
		int maxBounce{ 1 };
		std::vector<GameObject> const* scene{};
	};
}