
#include <Graphics.h>
#include <Window.h>
#include <glm/glm.hpp>
#include <AssetManager.h>
#include <Mesh.h>
#include <Camera.h>

namespace lux
{
	static Camera fpsCam;
	
	void GraphicSystem::Init()
	{
		pboRenderer.Init(Window::width, Window::height);
		AssetManager<Mesh>::Load("cube", Mesh("../assets/models/cube.fbx"));
		fpsCam = Camera(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f), 90.0, (double)Window::width / (double)Window::height);
	}

	void GraphicSystem::Update()
	{
		pboRenderer.BindPBO();


		for (int y{}; y < Window::height; ++y)
		{
			for (int x{}; x < Window::width; ++x)
			{
				//Shoot ray from camera
				auto u = (float)x / (Window::width - 1);
				auto v = (float)y / (Window::height - 1);
				Ray ray(fpsCam.origin, fpsCam.botLeftVP + u * fpsCam.horzVec + v * fpsCam.horzVec);
				pboRenderer.WritePixel(x, y, ray.direction);
			}
		}
		

		pboRenderer.Render();
	}

	void GraphicSystem::UnInit()
	{

	}
}