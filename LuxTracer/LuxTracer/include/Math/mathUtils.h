#pragma once

#include <limits>
#include <cstdlib>

namespace lux::math
{
	inline constexpr float inf = std::numeric_limits<float>::infinity();
	inline constexpr float pi = 3.141592635897932385f;
	inline constexpr float pi2 = 3.141592635897932385f * 2.0f;

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

	inline math::vec3 random_cos_weighted()
	{
		float z = random_float() * 2.0f - 1.0f;
		float a = random_float() * pi2;
		float r = sqrtf(1.0f - z*z);
		float x = r * cosf(a);
		float y = r * sinf(a);
		return math::vec3(x, y, z);
	}

	inline float clamp_float(float min, float max, float val)
	{
		return (val < min) ? min : (val > max) ? max : val;
	}
}