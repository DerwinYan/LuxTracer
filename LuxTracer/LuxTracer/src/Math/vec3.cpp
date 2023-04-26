#include <Math/vec3.h>
#include <Logger.h>

namespace lux::math
{
	vec3::vec3() : data{ 0.0f, 0.0f, 0.0f } {}
	vec3::vec3(float const val) : data{ val, val, val } {}
	vec3::vec3(float const x, float const y, float const z) : data{ x,y,z } {}

	vec3 const vec3::operator-() const
	{
		return vec3(-x, -y, -z);
	}

	vec3 const vec3::operator+(vec3 const& rhs) const
	{
		return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	vec3 const vec3::operator-(vec3 const& rhs) const
	{
		return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	vec3 const vec3::operator*(vec3 const& rhs) const
	{
		return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	vec3 const vec3::operator/(vec3 const& rhs) const
	{
		LogAssert(rhs.x || rhs.y || rhs.x, "Attempted division by 0!");
		return vec3(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	vec3 const vec3::operator+(float const val) const
	{
		return vec3(x + val, y + val, z + val);
	}

	vec3 const vec3::operator-(float const val) const
	{
		return vec3(x - val, y - val, z - val);
	}

	vec3 const vec3::operator*(float const val) const
	{
		return vec3(x * val, y * val, z * val);
	}

	vec3 const vec3::operator/(float const val) const
	{
		LogAssert(val, "Attempted division by 0!");
		return vec3(x / val, y / val, z / val);
	}

	vec3& vec3::operator+=(vec3 const& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	vec3& vec3::operator-=(vec3 const& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	vec3& vec3::operator*=(vec3 const& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	vec3& vec3::operator/=(vec3 const& rhs)
	{
		LogAssert(rhs.x || rhs.y || rhs.x, "Attempted division by 0!");
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	vec3& vec3::operator+=(float const val)
	{
		x += val;
		y += val;
		z += val;
		return *this;
	}

	vec3& vec3::operator-=(float const val)
	{
		x -= val;
		y -= val;
		z -= val;
		return *this;
	}

	vec3& vec3::operator*=(float const val)
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	vec3& vec3::operator/=(float const val)
	{
		x /= val;
		y /= val;
		z /= val;
		return *this;
	}

	bool vec3::operator==(vec3 const& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	bool vec3::operator!=(vec3 const& rhs) const
	{
		return x != rhs.x && y != rhs.y && z != rhs.z;
	}

	std::ostream& operator<<(std::ostream& os, vec3 const& rhs)
	{
		return os << rhs.x << ", " << rhs.y << ", " << rhs.z;
	}

	vec3 const operator+(float const val, vec3 const& rhs)
	{
		return vec3(rhs.x + val, rhs.y + val, rhs.z + val);
	}

	vec3 const operator-(float const val, vec3 const& rhs)
	{
		return vec3(rhs.x - val, rhs.y - val, rhs.z - val);
	}

	vec3 const operator*(float const val, vec3 const& rhs)
	{
		return vec3(rhs.x * val, rhs.y * val, rhs.z * val);
	}

	vec3 const operator/(float const val, vec3 const& rhs)
	{
		return vec3(rhs.x / val, rhs.y / val, rhs.z / val);
	}

	float Dot(vec3 const& lhs, vec3 const& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	float Length(vec3 const& lhs)
	{
		return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y + lhs.z * lhs.z);
	}

	float LengthSq(vec3 const& lhs)
	{
		return lhs.x * lhs.x + lhs.y * lhs.y + lhs.z * lhs.z;
	}

	float Distance(vec3 const& lhs, vec3 const& rhs)
	{
		vec3 vec = rhs - lhs;
		return Length(vec);
	}

	float DistanceSq(vec3 const& lhs, vec3 const& rhs)
	{
		vec3 vec = rhs - lhs;
		return LengthSq(vec);
	}

	vec3 const Normalize(vec3 const& lhs)
	{
		float length = Length(lhs);
		return lhs / length;
	}

	vec3 const Cross(vec3 const& lhs, vec3 const& rhs)
	{
		return vec3(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}
    vec3 const Lerp(vec3 const& start, vec3 const& end, float const t)
    {
			vec3 vector = end - start;
			return start + vector * t;
    }
}