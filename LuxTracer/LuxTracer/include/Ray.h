#pragma once

#include <Math/dvec3.h>

namespace lux
{
	struct Ray
	{
		Ray() = default;
		Ray(math::dvec3 const& pos, math::dvec3 const& dir);

		math::dvec3 const At(double t) const noexcept;

		math::dvec3 position{};
		math::dvec3 direction{};
	};
}