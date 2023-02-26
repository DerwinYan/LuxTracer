
#include <Ray.h>

namespace lux
{
	Ray::Ray(vec3 const& origin, vec3 const& direction)
		: origin{ origin }, direction{ direction }
	{}

	vec3 const Ray::GetOrigin() const
	{
		return origin;
	}

	vec3 const Ray::GetDirection() const
	{
		return direction;
	}

	vec3 const Ray::At(double t) const
	{
		return origin + direction * t;
	}
}