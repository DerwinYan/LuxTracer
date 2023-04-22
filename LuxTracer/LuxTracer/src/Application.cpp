#include <Application.h>
#include <Window.h>
#include <Systems/CommonSystems.h>

namespace lux
{
	//Create systems
	void Application::Init()
	{
		Window::CreateWindow(1280, 720, "Lux Tracer");
		Graphics::Init();
	}

	//Update systems
	void Application::Update()
	{
		while (Window::IsOpen())
		{
			Graphics::Update();
			Window::SwapBuffer();
		}
	}

	//Release systems
	void Application::UnInit()
	{
		Window::TerminateWindow();
		Graphics::UnInit();
	}
}