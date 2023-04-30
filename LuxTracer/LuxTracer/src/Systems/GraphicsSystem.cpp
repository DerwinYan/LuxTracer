#include <iostream>
#include <Window.h>
#include <Ray.h>
#include <Mesh.h>
#include <PathTracer.h>
#include <Camera.h>
#include <ThreadPool/RenderThreadPool.h>

namespace lux
{
	//Mesh cube;
	static PathTracer pt;
	static Camera cam;
	static RenderThreadPool rtp;
	
	template<typename BaseSystem>
	void GraphicsSystem<BaseSystem>::Init()
	{
		pbo.Init(Window::width, Window::height);
		pt.SetSamples(1);
		pt.SetBounce(8);
		rtp.Initialize();
	}

	template<typename BaseSystem>
	void GraphicsSystem<BaseSystem>::Update()
	{
		if (shouldClear)
		{
			pbo.Clear();
			shouldClear = false;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		pbo.Bind();

		pt.LinkScene(BaseSystem::scene);

		TiledRenderData::SceneParams params(&cam, &pbo, &pt);
		unsigned threadsAvail = rtp.GetNumThreads();

		//Goal: Split output buffer into tiles of 64x64 bytes (16x16 pixels)
		int const tileSize = 16;
		for (int j{}; j < pbo.imgHeight; j+= tileSize)
		{
			for (int i{}; i < pbo.imgWidth; i+= tileSize)
			{
				TiledRenderData renderData;
				int startX = i;
				int startY = j;
				int endX = i + tileSize;
				int endY = j + tileSize;
				if (endX + tileSize >= pbo.imgWidth)
					endX = pbo.imgWidth - 1;
				if (endY + tileSize >= pbo.imgHeight)
					endY = pbo.imgHeight - 1;

				renderData.InitData(startX, endX, startY, endY, params);
				rtp.QueueJob(renderData);
			}
		}


		rtp.WaitComplete();

		pbo.Render();
	}

	template<typename BaseSystem>
	void GraphicsSystem<BaseSystem>::UnInit()
	{
		rtp.Terminate();
	}
}

