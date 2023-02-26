#pragma once
#include <vector>
#include <math/vecx.h>

namespace lux
{
	class Mesh
	{
	public:
		Mesh(std::string_view const& filePath);

		struct VertexData
		{
			vec3 pos{};
			vec3 normal{};
		};

		struct Triangle
		{
			VertexData vertices[3]{};
		};
	private:
		std::vector<Triangle> triangles{};
	};
}