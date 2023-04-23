#pragma once

#include <iostream>

namespace lux::math
{
	union dvec3
	{
		struct { double data[3]; };
		struct { double x; double y; double z; };
		struct { double r; double g; double b; };

		dvec3();
		dvec3(double const val);
		dvec3(double const x, double const y, double const z);
		dvec3(dvec3 const& rhs) = default;
		dvec3& operator=(dvec3 const& rhs) = default;

		dvec3 const operator-() const;

		dvec3 const operator+(dvec3 const& rhs) const;
		dvec3 const operator-(dvec3 const& rhs) const;
		dvec3 const operator*(dvec3 const& rhs) const;
		dvec3 const operator/(dvec3 const& rhs) const;

		dvec3 const operator+(double const val) const;
		dvec3 const operator-(double const val) const;
		dvec3 const operator*(double const val) const;
		dvec3 const operator/(double const val) const;

		dvec3& operator+=(dvec3 const& rhs);
		dvec3& operator-=(dvec3 const& rhs);
		dvec3& operator*=(dvec3 const& rhs);
		dvec3& operator/=(dvec3 const& rhs);

		dvec3& operator+=(double const val);
		dvec3& operator-=(double const val);
		dvec3& operator*=(double const val);
		dvec3& operator/=(double const val);

		bool operator==(dvec3 const& rhs) const;
		bool operator!=(dvec3 const& rhs) const;

	};

	std::ostream& operator<<(std::ostream &os, dvec3 const& rhs);
	
	dvec3 const operator+(double const val, dvec3 const& rhs);
	dvec3 const operator-(double const val, dvec3 const& rhs);
	dvec3 const operator*(double const val, dvec3 const& rhs);
	dvec3 const operator/(double const val, dvec3 const& rhs);

	double Dot(dvec3 const& lhs, dvec3 const& rhs);
	double Length(dvec3 const& lhs);
	double LengthSq(dvec3 const& lhs);
	double Distance(dvec3 const& lhs, dvec3 const& rhs);
	double DistanceSq(dvec3 const& lhs, dvec3 const& rhs);
	dvec3 const Normalize(dvec3 const& lhs);
	dvec3 const Cross(dvec3 const& lhs, dvec3 const& rhs);
	dvec3 const Lerp(dvec3 const& start, dvec3 const& end, double const t);
}