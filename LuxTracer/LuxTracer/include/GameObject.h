#pragma once

#include <Math/vec3.h>
#include <Mesh.h>

namespace lux
{
	struct Material
	{
		Material(math::vec3 const& col, math::vec3 const& emissionCol = math::vec3{}, float const emissionStrength = 0.0f)
			: color{ col }, emission{ emissionCol }, emissionStr{ emissionStrength } {}

		math::vec3 color{ 1.0f };
		math::vec3 emission{};
		float emissionStr{};
	};

	struct GameObject
	{
		GameObject(math::vec3 const& pos, float const rad, Material const& mat)
			: position{ pos }, radius{ rad }, mat{ mat } {}

		math::vec3 position;
		float radius;
		Material mat;
	};
}