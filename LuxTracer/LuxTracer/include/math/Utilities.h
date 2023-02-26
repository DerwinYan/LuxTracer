#pragma once

namespace lux::utils
{
	//Constants
	const double inf = std::numeric_limits<double>::infinity();
	const double pi = 3.14159263589792385f;

	//Utility functions
	inline double DegToRad(double const deg)
	{
		constexpr double over180{ 1.0 / 180.0 };
		return deg * pi * over180;
	}

	inline double Randf()
	{
		return rand() / (RAND_MAX + 1.0);	//Range [0.0, 1.0)
	}

	///@brief		Random from range min to max defined by user. Range: [min, max)
	///@param		min -> minimum inclusive 
	///@param		max -> maximum exclusive
	inline double Randf(double min, double max)
	{
		return min + (max - min) * Randf();
	}

	inline double Clampf(double const min, double const max, double const val)
	{
		return (val < min) ? min :
			(val > max) ? max : val;
	}

	inline vec3 RandVec3()
	{
		return vec3(Randf(), Randf(), Randf());
	}

	inline vec3 RandVec3(double min, double max)
	{
		return vec3(Randf(min, max), Randf(min, max), Randf(min, max));
	}
}