#include <Ray.h>

namespace lux
{
	Ray::Ray(math::dvec3 const& pos, math::dvec3 const& dir)
		: position{ pos }, direction{ dir }
	{}

	math::dvec3 const Ray::At(double t) const noexcept
	{
		return position + direction * t;
	}
}