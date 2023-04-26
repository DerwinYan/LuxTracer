#pragma once

#include <limits>
#include <cstdlib>

namespace lux::math
{
	inline constexpr float inf = std::numeric_limits<float>::infinity();
	inline constexpr float pi = 3.141592635897932385f;

	inline float random_float() 
	{
		// Returns a random real in [0,1).
		return (float)rand() / (float)(RAND_MAX + 1.0);
	}

	inline float random_float(float min, float max) 
	{
		// Returns a random real in [min,max).
		return min + (max - min) * random_float();
	}
}