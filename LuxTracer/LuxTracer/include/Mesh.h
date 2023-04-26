#pragma once

#include <vector>
#include <string>
#include <Math/vec3.h>

namespace lux
{
	struct Mesh
	{
		Mesh() = default;
		Mesh(std::string_view const& filePath);

		struct Vertex
		{
			math::vec3 pos{};
			//math::dvec3 normal{};
			//math::dvec2 uv{};
		};

		struct Triangle
		{
			Vertex vertices[3]{};
		};

		std::vector<Triangle> triangles{}; //local space triangle for pathtracing
	};
}