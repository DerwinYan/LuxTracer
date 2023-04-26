#include <Ray.h>

namespace lux
{
	Ray::Ray(math::vec3 const& pos, math::vec3 const& dir)
		: position{ pos }, direction{ dir }
	{}

	math::vec3 const Ray::At(float t) const noexcept
	{
		return position + direction * t;
	}
}