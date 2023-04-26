#pragma once

namespace lux
{
	struct Timer
	{
		static void StartFrame(float time)
		{
			startTime = time;
		}

		static void EndFrame(float time)
		{
			dt = time - startTime;
		}

		inline static float dt{};

	private:
		inline static float startTime{};
	};
}