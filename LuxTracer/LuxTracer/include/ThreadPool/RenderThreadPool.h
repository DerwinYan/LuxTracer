#pragma once

#include <functional>
#include <thread>
#include <mutex>
#include <queue>
#include <pbo.h>
#include <Camera.h>
#include <GameObject.h>
#include <PathTracer.h>

namespace lux
{
	struct TiledRenderData
	{
		struct SceneParams
		{
			Camera const* cam{};
			Pbo* pbo{};
			PathTracer* pt{};
		};

		void InitData(int _startX, int _endX, int _startY, int _endY, SceneParams const& params)
		{
			startX = _startX;
			endX = _endX;
			startY = _startY;
			endY = _endY;
			sceneParams = params;
		}

		void Run()
		{
			for (int j{ startY }; j < endY; ++j)
			{
				for (int i{ startX }; i < endX; ++i)
				{
					sceneParams.pbo->WritePixel(i, j, 
						sceneParams.pt->GenerateRay(i, j, sceneParams.pbo->imgWidth, sceneParams.pbo->imgHeight, 
						*sceneParams.cam));
				}
			}
		}

		int startX{}, endX{ 1 };
		int startY{}, endY{ 1 };
		SceneParams sceneParams{};
	};

	struct RenderThreadPool
	{
		void Initialize();
		void Terminate();
		void WaitComplete();
		void QueueJob(TiledRenderData const& job);

		inline unsigned GetNumThreads() const noexcept
		{
			return maxThreads;
		}

	private:
		void ThreadUpdate();

		bool isTerminate{};
		unsigned maxThreads{ 1 };

		unsigned busyThreads{};
		std::vector<std::thread> pool;
		std::queue<TiledRenderData> jobs;
		std::mutex jobMutex;
		std::condition_variable jobCondition;
		std::condition_variable idleCondition;
	};
}