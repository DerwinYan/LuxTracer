#pragma once

#include <Math/vec3.h>

namespace lux
{
	struct Ray
	{
		Ray() = default;
		Ray(math::vec3 const& pos, math::vec3 const& dir);

		math::vec3 const At(float t) const noexcept;

		math::vec3 position{};
		math::vec3 direction{};
	};
}