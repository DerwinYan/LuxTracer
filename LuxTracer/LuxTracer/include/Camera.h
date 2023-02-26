#pragma once

#include <math/vecx.h>
#include <Ray.h>

namespace lux
{
	class Camera
	{
	public:
		Camera(vec3 const& eye, vec3 const& target, vec3 const& up, double fov, double aspectRatio)
		{
			double theta = DegToRad(fov);
			double height = tan(theta / 2.0);
			double viewport_height = 2.0 * height;
			double viewport_width = aspectRatio * viewport_height;
			double focal_length = 1.0;

			vec3 forwardVec = Normalize(eye - target);
			vec3 rightVec = Normalize(Cross(up, forwardVec));
			vec3 upVec = Cross(forwardVec, rightVec);

			origin = eye;
			horzVec = viewport_width * rightVec;
			vertVec = viewport_height * upVec;
			botLeftVP = origin - horzVec * 0.5f - vertVec * 0.5f - forwardVec;
		}

		Ray const DrawRay(double u, double v) const
		{
			return Ray(origin, botLeftVP + u * horzVec + v * vertVec - origin);
		}

	private:
		vec3 origin{};
		vec3 horzVec{};
		vec3 vertVec{};
		vec3 botLeftVP{};
	};
}