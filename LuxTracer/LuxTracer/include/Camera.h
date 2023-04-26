#pragma once

#include <Math/vec3.h>
#include <Ray.h>

namespace lux
{
	struct Camera
	{
		Camera()
		{
			float aspect = 16.0f / 9.0f;
			float ndcHeight = 2.0f;
			float ndcWidth = aspect * ndcHeight;
			float focalLength = 1.0f;

			horizontal = math::vec3(ndcWidth, 0.0f, 0.0f);
			vertical = math::vec3(0.0f, ndcHeight, 0.0f);
			btmLeftNDC = position - horizontal * 0.5f - vertical * 0.5f - math::vec3(0.0f, 0.0f, focalLength);
		}

		Ray const GetRay(float u, float v) const
		{
			return Ray(position, btmLeftNDC + u * horizontal + v * vertical - position);
		}
	
		math::vec3 position{};
		math::vec3 btmLeftNDC{};
		math::vec3 horizontal{};
		math::vec3 vertical{};
	};
}