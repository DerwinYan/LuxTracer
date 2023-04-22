#pragma once

#include <Math/dvec3.h>
#include <Mesh.h>

namespace lux
{
	struct GameObject
	{
		math::dvec3 transform;
		math::dvec3 rotation;
		math::dvec3 scale{ 1.0 };

		Mesh* mesh;
		//Material* material
	};
}