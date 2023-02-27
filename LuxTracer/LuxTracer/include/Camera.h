#pragma once

#include <Ray.h>

namespace lux
{
	class Camera
	{
	public:
		Camera(glm::vec3 const& eye, glm::vec3 const& target, glm::vec3 const& up, double fov, double aspectRatio)
		{
			float theta = glm::radians(fov);
			float height = tan(theta / 2.0);
			float viewport_height = 2.0 * height;
			float viewport_width = aspectRatio * viewport_height;
			float focal_length = 1.0;

			glm::vec3 forwardVec = glm::normalize(eye - target);
			glm::vec3 rightVec = glm::normalize(glm::cross(up, forwardVec));
			glm::vec3 upVec = glm::cross(forwardVec, rightVec);

			origin = eye;
			horzVec = viewport_width * rightVec;
			vertVec = viewport_height * upVec;
			botLeftVP = origin - horzVec * 0.5f - vertVec * 0.5f - forwardVec;
		}

		Ray const DrawRay(float u, float v) const
		{
			return Ray(origin, botLeftVP + u * horzVec + v * vertVec - origin);
		}

	private:
		glm::vec3 origin{};
		glm::vec3 horzVec{};
		glm::vec3 vertVec{};
		glm::vec3 botLeftVP{};
	};
}