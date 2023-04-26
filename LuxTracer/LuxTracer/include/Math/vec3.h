#pragma once

#include <iostream>

namespace lux::math
{
	union vec3
	{
		struct { float data[3]; };
		struct { float x; float y; float z; };
		struct { float r; float g; float b; };

		vec3();
		vec3(float const val);
		vec3(float const x, float const y, float const z);
		vec3(vec3 const& rhs) = default;
		vec3& operator=(vec3 const& rhs) = default;

		vec3 const operator-() const;

		vec3 const operator+(vec3 const& rhs) const;
		vec3 const operator-(vec3 const& rhs) const;
		vec3 const operator*(vec3 const& rhs) const;
		vec3 const operator/(vec3 const& rhs) const;

		vec3 const operator+(float const val) const;
		vec3 const operator-(float const val) const;
		vec3 const operator*(float const val) const;
		vec3 const operator/(float const val) const;

		vec3& operator+=(vec3 const& rhs);
		vec3& operator-=(vec3 const& rhs);
		vec3& operator*=(vec3 const& rhs);
		vec3& operator/=(vec3 const& rhs);

		vec3& operator+=(float const val);
		vec3& operator-=(float const val);
		vec3& operator*=(float const val);
		vec3& operator/=(float const val);

		bool operator==(vec3 const& rhs) const;
		bool operator!=(vec3 const& rhs) const;

	};

	std::ostream& operator<<(std::ostream &os, vec3 const& rhs);
	
	vec3 const operator+(float const val, vec3 const& rhs);
	vec3 const operator-(float const val, vec3 const& rhs);
	vec3 const operator*(float const val, vec3 const& rhs);
	vec3 const operator/(float const val, vec3 const& rhs);

	float Dot(vec3 const& lhs, vec3 const& rhs);
	float Length(vec3 const& lhs);
	float LengthSq(vec3 const& lhs);
	float Distance(vec3 const& lhs, vec3 const& rhs);
	float DistanceSq(vec3 const& lhs, vec3 const& rhs);
	vec3 const Normalize(vec3 const& lhs);
	vec3 const Cross(vec3 const& lhs, vec3 const& rhs);
	vec3 const Lerp(vec3 const& start, vec3 const& end, float const t);
}