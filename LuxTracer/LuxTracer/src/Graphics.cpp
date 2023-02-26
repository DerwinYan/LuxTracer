
#include <Graphics.h>
#include <Window.h>

namespace lux
{
	void GraphicSystem::Init()
	{
		pboRenderer.Init(Window::width, Window::height);
	}

	void GraphicSystem::Update()
	{

		pboRenderer.Render();
	}

	void GraphicSystem::UnInit()
	{

	}
}