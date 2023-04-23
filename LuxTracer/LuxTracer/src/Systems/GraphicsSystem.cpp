#include <iostream>
#include <Window.h>
#include <Ray.h>
#include <Mesh.h>
#include <PathTracer.h>

namespace lux
{
	//Mesh cube;
	static PathTracer pt;
	
	template<typename BaseSystem>
	void GraphicsSystem<BaseSystem>::Init()
	{
		pbo.Init(Window::width, Window::height);

		//cube = Mesh("../assets/models/cube.fbx");
	}

	template<typename BaseSystem>
	void GraphicsSystem<BaseSystem>::Update()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		pbo.Bind();

		//Camera
		double aspectRatio = (double)pbo.imgWidth / (double)pbo.imgHeight;
		double viewportHeight = 2.0;
		double viewportWidth = aspectRatio * viewportHeight;
		double focalLength = 1.0;
		math::dvec3 camPos{0.0, 0.0, 0.0};
		math::dvec3 horizontal(viewportWidth, 0.0, 0.0);
		math::dvec3 vertical(0.0, viewportHeight, 0.0);
		math::dvec3 lowerLeftCorner = camPos - horizontal * 0.5 - vertical * 0.5 - math::dvec3(0.0, 0.0, focalLength);

		for (int j{}; j < pbo.imgHeight; ++j)
		{
			for (int i{}; i < pbo.imgWidth; ++i)
			{
				//Calculate camera ray
				double x = (double)i / (pbo.imgWidth - 1);
				double y = (double)j / (pbo.imgHeight - 1);
				Ray camRay(camPos, lowerLeftCorner + x * horizontal + y * vertical - camPos);

				pbo.WritePixel(i, j, pt.TraceRay(camRay, BaseSystem::scene));
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

