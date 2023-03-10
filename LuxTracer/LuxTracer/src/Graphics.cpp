
#include <Graphics.h>
#include <Window.h>
#include <glm/glm.hpp>

namespace lux
{
	void GraphicSystem::Init()
	{
		pboRenderer.Init(Window::width, Window::height);
	}

	void GraphicSystem::Update()
	{
		pboRenderer.BindPBO();


		for (int y{}; y < Window::height; ++y)
		{
			for (int x{}; x < Window::width; ++x)
			{
				pboRenderer.WritePixel(x, y, glm::vec3{ 1.0,0.0,0.0 });
			}
		}
		

		pboRenderer.Render();
	}

	void GraphicSystem::UnInit()
	{

	}
}