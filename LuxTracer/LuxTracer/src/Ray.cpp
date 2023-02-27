
#include <Ray.h>

namespace lux
{
	Ray::Ray(glm::vec3 const& origin, glm::vec3 const& direction)
		: origin{ origin }, direction{ direction }
	{}

	glm::vec3 const Ray::GetOrigin() const
	{
		return origin;
	}

	glm::vec3 const Ray::GetDirection() const
	{
		return direction;
	}

	glm::vec3 const Ray::At(float t) const
	{
		return origin + direction * t;
	}
}