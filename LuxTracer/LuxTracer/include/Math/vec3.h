#pragma once

#include <iostream>
#include <smmintrin.h>
#include <Logger.h>

namespace lux::math
{
	union vec3
	{
		struct { float data[3]; };
		struct { float x; float y; float z; };
		struct { float r; float g; float b; };
		__m128 vector;

		//Targets sign bit of floating point (Thanks to https://github.com/pelletier/vector3/blob/master/vector3.h)
		inline static const __m128 SIGNMASK = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));

		vec3() : vector{ _mm_setzero_ps() } {}
		vec3(float const val) : vector{ _mm_set_ps1(val) } {}
		vec3(float const x, float const y, float const z) : vector{ _mm_set_ps(1.0f, z, y, x) } {}
		vec3(__m128 const& vector) : vector{ vector } {}
		vec3(vec3 const& rhs) : vector{ rhs.vector } {}
		vec3& operator=(vec3 const& rhs) { _mm_store_ps(data, rhs.vector); return *this; }

		inline vec3 const operator-() const { return vec3(_mm_xor_ps(vector, SIGNMASK)); }

		inline vec3 const operator+(vec3 const& rhs) const { return vec3(_mm_add_ps(vector, rhs.vector)); }
		inline vec3 const operator-(vec3 const& rhs) const { return vec3(_mm_sub_ps(vector, rhs.vector)); }
		inline vec3 const operator*(vec3 const& rhs) const { return vec3(_mm_mul_ps(vector, rhs.vector)); }
		inline vec3 const operator/(vec3 const& rhs) const
		{
			LogAssert(rhs.x || rhs.y || rhs.x, "Attempted division by 0!");
			return vec3(_mm_div_ps(vector, rhs.vector));
		}
		 
		inline vec3 const operator+(float const val) const { return vec3(_mm_add_ps(vector, _mm_set_ps1(val))); }
		inline vec3 const operator-(float const val) const { return vec3(_mm_sub_ps(vector, _mm_set_ps1(val))); }
		inline vec3 const operator*(float const val) const { return vec3(_mm_mul_ps(vector, _mm_set_ps1(val))); }
		inline vec3 const operator/(float const val) const
		{
			LogAssert(val, "Attempted division by 0!");
			return vec3(_mm_div_ps(vector, _mm_set_ps1(val)));
		}

		inline vec3& operator+=(vec3 const& rhs) { vector = _mm_add_ps(vector, rhs.vector); return *this; }
		inline vec3& operator-=(vec3 const& rhs) { vector = _mm_sub_ps(vector, rhs.vector); return *this; }
		inline vec3& operator*=(vec3 const& rhs) { vector = _mm_mul_ps(vector, rhs.vector); return *this; }
		inline vec3& operator/=(vec3 const& rhs)
		{
			LogAssert(rhs.x || rhs.y || rhs.x, "Attempted division by 0!");
			vector = _mm_div_ps(vector, rhs.vector);
			return *this;
		}
		 
		inline vec3& operator+=(float const val) { vector = _mm_add_ps(vector, _mm_set_ps1(val)); return *this; }
		inline vec3& operator-=(float const val) { vector = _mm_sub_ps(vector, _mm_set_ps1(val)); return *this; }
		inline vec3& operator*=(float const val) { vector = _mm_mul_ps(vector, _mm_set_ps1(val)); return *this; }
		inline vec3& operator/=(float const val)
		{
			LogAssert(val, "Attempted division by 0!");
			vector = _mm_div_ps(vector, _mm_set_ps1(val));
			return *this;
		}

		inline bool operator==(vec3 const& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
		inline bool operator!=(vec3 const& rhs) const { return x != rhs.x && y != rhs.y && z != rhs.z; }

	};

	std::ostream& operator<<(std::ostream &os, vec3 const& rhs);
	
	inline vec3 const operator+(float const val, vec3 const& rhs) { return vec3(_mm_add_ps(rhs.vector, _mm_set_ps1(val))); }
	inline vec3 const operator-(float const val, vec3 const& rhs) { return vec3(_mm_sub_ps(rhs.vector, _mm_set_ps1(val))); }
	inline vec3 const operator*(float const val, vec3 const& rhs) { return vec3(_mm_mul_ps(rhs.vector, _mm_set_ps1(val))); }
	inline vec3 const operator/(float const val, vec3 const& rhs)
	{
		LogAssert(val, "Attempted division by 0!");
		return vec3(_mm_div_ps(rhs.vector, _mm_set_ps1(val)));
	}

	inline float Dot(vec3 const& lhs, vec3 const& rhs)
	{
		vec3 tempMul = lhs * rhs;
		return tempMul.x + tempMul.y + tempMul.z;
	}

	inline float Length(vec3 const& lhs)
	{
		return std::sqrt(Dot(lhs, lhs));
	}

	inline float LengthSq(vec3 const& lhs)
	{
		return Dot(lhs, lhs);
	}

	inline float Distance(vec3 const& lhs, vec3 const& rhs)
	{
		return Length(rhs - lhs);
	}

	inline float DistanceSq(vec3 const& lhs, vec3 const& rhs)
	{
		return LengthSq(rhs - lhs);
	}

	inline vec3 const Normalize(vec3 const& lhs)
	{
		float length = Length(lhs);
		return lhs / length;
	}

	inline vec3 const Cross(vec3 const& lhs, vec3 const& rhs)
	{
		//return vec3(
		//	lhs.y * rhs.z - lhs.z * rhs.y,
		//	lhs.z * rhs.x - lhs.x * rhs.z,
		//	lhs.x * rhs.y - lhs.y * rhs.x
		//);

		//Thanks to https://github.com/pelletier/vector3/blob/master/vector3.h
		return _mm_sub_ps(
			_mm_mul_ps(_mm_shuffle_ps(lhs.vector, lhs.vector, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(rhs.vector, rhs.vector, _MM_SHUFFLE(3, 1, 0, 2))),
			_mm_mul_ps(_mm_shuffle_ps(lhs.vector, lhs.vector, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(rhs.vector, rhs.vector, _MM_SHUFFLE(3, 0, 2, 1)))
		);
	}

	inline vec3 const Lerp(vec3 const& start, vec3 const& end, float const t)
	{
		vec3 vector = end - start;
		return start + vector * t;
	}
}