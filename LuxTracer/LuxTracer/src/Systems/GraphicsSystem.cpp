#include <iostream>
#include <Window.h>
#include <Ray.h>
#include <Mesh.h>
#include <PathTracer.h>
#include <Camera.h>

namespace lux
{
	//Mesh cube;
	static PathTracer pt;
	static Camera cam;
	
	template<typename BaseSystem>
	void GraphicsSystem<BaseSystem>::Init()
	{
		pbo.Init(Window::width, Window::height);
		pt.SetSamples(4);

		//cube = Mesh("../assets/models/cube.fbx");
	}

	template<typename BaseSystem>
	void GraphicsSystem<BaseSystem>::Update()
	{
		srand(0);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		pbo.Bind();

		for (int j{}; j < pbo.imgHeight; ++j)
		{
			for (int i{}; i < pbo.imgWidth; ++i)
			{
				//Calculate camera ray
				//double x = (double)i / (pbo.imgWidth - 1);
				//double y = (double)j / (pbo.imgHeight - 1);

				pbo.WritePixel(i, j, pt.GenerateRay(i, j, pbo.imgWidth, pbo.imgHeight, cam, BaseSystem::scene));
				//pbo.WritePixel(i, j, pt.GenerateRay(cam.GetRay(x,y), BaseSystem::scene));
			}
		}

		pbo.Render();
	}

	template<typename BaseSystem>
	void GraphicsSystem<BaseSystem>::UnInit()
	{
		std::cout << "Graphics unInit!\n";
	}
}

