#pragma once

namespace lux
{
	struct Timer
	{
		static void StartFrame(double time)
		{
			startTime = time;
		}

		static void EndFrame(double time)
		{
			dt = time - startTime;
		}

		inline static double dt{};

	private:
		inline static double startTime{};
	};
}