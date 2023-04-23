#pragma once

#include <Math/dvec3.h>
#include <Ray.h>

namespace lux
{
	struct Camera
	{
		Camera()
		{
			double aspect = 16.0 / 9.0;
			double ndcHeight = 2.0;
			double ndcWidth = aspect * ndcHeight;
			double focalLength = 1.0;

			horizontal = math::dvec3(ndcWidth, 0.0, 0.0);
			vertical = math::dvec3(0.0, ndcHeight, 0.0);
			btmLeftNDC = position - horizontal * 0.5 - vertical * 0.5 - math::dvec3(0.0, 0.0, focalLength);
		}

		Ray const GetRay(double u, double v) const
		{
			return Ray(position, btmLeftNDC + u * horizontal + v * vertical - position);
		}
	
		math::dvec3 position{};
		math::dvec3 btmLeftNDC{};
		math::dvec3 horizontal{};
		math::dvec3 vertical{};
	};
}