#include <Math/dvec3.h>
#include <Logger.h>

namespace lux::math
{
	dvec3::dvec3() : data{ 0.0, 0.0, 0.0 } {}
	dvec3::dvec3(double const val) : data{ val, val, val } {}
	dvec3::dvec3(double const x, double const y, double const z) : data{ x,y,z } {}

	dvec3 const dvec3::operator-() const
	{
		return dvec3(-x, -y, -z);
	}

	dvec3 const dvec3::operator+(dvec3 const& rhs) const
	{
		return dvec3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	dvec3 const dvec3::operator-(dvec3 const& rhs) const
	{
		return dvec3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	dvec3 const dvec3::operator*(dvec3 const& rhs) const
	{
		return dvec3(x * rhs.x, y * rhs.y, z * rhs.z);
	}

	dvec3 const dvec3::operator/(dvec3 const& rhs) const
	{
		LogAssert(x || y || x, "Attempted division by 0!");
		return dvec3(x / rhs.x, y / rhs.y, z / rhs.z);
	}

	dvec3 const dvec3::operator+(double const val) const
	{
		return dvec3(x + val, y + val, z + val);
	}

	dvec3 const dvec3::operator-(double const val) const
	{
		return dvec3(x - val, y - val, z - val);
	}

	dvec3 const dvec3::operator*(double const val) const
	{
		return dvec3(x * val, y * val, z * val);
	}

	dvec3 const dvec3::operator/(double const val) const
	{
		LogAssert(x || y || x, "Attempted division by 0!");
		return dvec3(x / val, y / val, z / val);
	}

	dvec3& dvec3::operator+=(dvec3 const& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	dvec3& dvec3::operator-=(dvec3 const& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	dvec3& dvec3::operator*=(dvec3 const& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	dvec3& dvec3::operator/=(dvec3 const& rhs)
	{
		LogAssert(x || y || x, "Attempted division by 0!");
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	dvec3& dvec3::operator+=(double const val)
	{
		x += val;
		y += val;
		z += val;
		return *this;
	}

	dvec3& dvec3::operator-=(double const val)
	{
		x -= val;
		y -= val;
		z -= val;
		return *this;
	}

	dvec3& dvec3::operator*=(double const val)
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	dvec3& dvec3::operator/=(double const val)
	{
		x /= val;
		y /= val;
		z /= val;
		return *this;
	}

	bool dvec3::operator==(dvec3 const& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	bool dvec3::operator!=(dvec3 const& rhs) const
	{
		return x != rhs.x && y != rhs.y && z != rhs.z;
	}

	std::ostream& operator<<(std::ostream& os, dvec3 const& rhs)
	{
		return os << rhs.x << ", " << rhs.y << ", " << rhs.z;
	}

	dvec3 const operator+(double const val, dvec3 const& rhs)
	{
		return dvec3(rhs.x + val, rhs.y + val, rhs.z + val);
	}

	dvec3 const operator-(double const val, dvec3 const& rhs)
	{
		return dvec3(rhs.x - val, rhs.y - val, rhs.z - val);
	}

	dvec3 const operator*(double const val, dvec3 const& rhs)
	{
		return dvec3(rhs.x * val, rhs.y * val, rhs.z * val);
	}

	dvec3 const operator/(double const val, dvec3 const& rhs)
	{
		return dvec3(rhs.x / val, rhs.y / val, rhs.z / val);
	}

	double Dot(dvec3 const& lhs, dvec3 const& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	double Length(dvec3 const& lhs)
	{
		return std::sqrt(lhs.x * lhs.x + lhs.y * lhs.y + lhs.z * lhs.z);
	}

	double LengthSq(dvec3 const& lhs)
	{
		return lhs.x * lhs.x + lhs.y * lhs.y + lhs.z * lhs.z;
	}

	double Distance(dvec3 const& lhs, dvec3 const& rhs)
	{
		dvec3 vec = rhs - lhs;
		return Length(vec);
	}

	double DistanceSq(dvec3 const& lhs, dvec3 const& rhs)
	{
		dvec3 vec = rhs - lhs;
		return LengthSq(vec);
	}

	dvec3 const Normalize(dvec3 const& lhs)
	{
		double length = Length(lhs);
		return lhs / length;
	}

	dvec3 const Cross(dvec3 const& lhs, dvec3 const& rhs)
	{
		return dvec3(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}
    dvec3 const Lerp(dvec3 const& start, dvec3 const& end, double const t)
    {
			dvec3 vector = end - start;
			return start + vector * t;
    }
}