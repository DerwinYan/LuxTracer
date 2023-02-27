#pragma once

#include <glm/glm.hpp>

namespace lux
{
	class Ray
	{
	public:
		Ray() = default;
		Ray(glm::vec3 const& origin, glm::vec3 const& direction);

		glm::vec3 const GetOrigin() const;
		glm::vec3 const GetDirection() const;

		glm::vec3 const At(float t) const;

	public:
		glm::vec3 origin{};
		glm::vec3 direction{};
	};
}