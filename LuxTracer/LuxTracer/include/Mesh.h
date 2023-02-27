#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace lux
{
	class Mesh
	{
	public:
		Mesh(std::string_view const& filePath);

		struct VertexData
		{
			glm::vec3 pos{};
			glm::vec3 normal{};
			glm::vec2 uv{};
		};

		struct Triangle
		{
			VertexData vertices[3]{};
		};
	private:
		std::vector<Triangle> triangles{};
	};
}