#include <Math/vec3.h>
#include <Logger.h>

namespace lux::math
{
	std::ostream& operator<<(std::ostream& os, vec3 const& rhs)
	{
		return os << rhs.x << ", " << rhs.y << ", " << rhs.z;
	}
}