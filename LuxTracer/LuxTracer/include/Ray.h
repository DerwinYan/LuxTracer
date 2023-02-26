#pragma once

#include <math/vecx.h>

namespace lux
{
	class Ray
	{
	public:
		Ray() = default;
		Ray(vec3 const& origin, vec3 const& direction);

		vec3 const GetOrigin() const;
		vec3 const GetDirection() const;

		vec3 const At(double t) const;

	public:
		vec3 origin{};
		vec3 direction{};
	};
}