#pragma once

#include <cmath>
#include <iostream>

namespace lux
{
	class vec3
	{
	public:
		//Constructors
		vec3();
		vec3(double val);
		vec3(double x, double y, double z);
		vec3(double vals[3]);
		vec3(vec3 const&) = default;
		vec3& operator=(vec3 const&) = default;

		//Member access functions
		double x() const;
		double y() const;
		double z() const;

		double r() const;
		double g() const;
		double b() const;

		//Negate operator
		vec3 operator-() const;

		//Element wise operations
		vec3 operator+(vec3 const& rhs) const;
		vec3 operator-(vec3 const& rhs) const;
		vec3 operator*(vec3 const& rhs) const;
		vec3 operator/(vec3 const& rhs) const;

		//Element wise operation on original class
		vec3& operator+=(vec3 const& rhs);
		vec3& operator-=(vec3 const& rhs);
		vec3& operator*=(vec3 const& rhs);
		vec3& operator/=(vec3 const& rhs);

		//Scalar operations
		vec3 operator*(double val) const;
		vec3 operator/(double val) const;

		//Scalar operations on original class
		vec3& operator*=(double val);
		vec3& operator/=(double val);

		bool operator==(vec3 const& v) const;
		bool operator!=(vec3 const& v) const;

	public:
		double data[3];
	};

	//Utility functions
	inline double Dot(vec3 const& lhs, vec3 const& rhs)
	{
		return lhs.data[0] * rhs.data[0] + lhs.data[1] * rhs.data[1] + lhs.data[2] * rhs.data[2];
	}

	inline double Length(vec3 const& lhs)
	{
		return std::sqrt(lhs.data[0] * lhs.data[0] + lhs.data[1] * lhs.data[1] + lhs.data[2] * lhs.data[2]);
	}

	inline double LengthSq(vec3 const& lhs)
	{
		return lhs.data[0] * lhs.data[0] + lhs.data[1] * lhs.data[1] + lhs.data[2] * lhs.data[2];
	}

	inline double Distance(vec3 const& lhs, vec3 const& rhs)
	{
		return std::sqrt(lhs.data[0] * rhs.data[0] + lhs.data[1] * rhs.data[1] + lhs.data[2] * rhs.data[2]);
	}

	inline double DistanceSq(vec3 const& lhs, vec3 const& rhs)
	{
		return lhs.data[0] * rhs.data[0] + lhs.data[1] * rhs.data[1] + lhs.data[2] * rhs.data[2];
	}

	inline vec3 Normalize(vec3 const& lhs)
	{
		return vec3 { lhs / Length(lhs) };
	}

	inline vec3 Cross(vec3 const& lhs, vec3 const& rhs)
	{
		return vec3
		{
			lhs.data[1] * rhs.data[2] - rhs.data[1] * lhs.data[2],
			lhs.data[2] * rhs.data[0] - rhs.data[2] * lhs.data[0],
			lhs.data[0] * rhs.data[1] - rhs.data[0] * lhs.data[1]
		};
	}

	inline vec3 operator*(vec3 const& lhs, vec3 const& rhs)
	{
		return vec3(lhs.data[0] * rhs.data[0], lhs.data[1] * rhs.data[1], lhs.data[2] * rhs.data[2]);
	}

	inline std::ostream& operator<<(std::ostream& os, vec3 const& rhs)
	{
		return os << rhs.data[0] << ", " << rhs.data[1] << ", " << rhs.data[2];
	}

	using color3 = vec3;
}