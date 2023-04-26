#include <Application.h>
#include <Window.h>
#include <Systems/CommonSystems.h>
#include <Timer.h>

namespace lux
{
	//Create systems
	void Application::Init()
	{
		//Window::CreateWindow(400, 225, "Lux Tracer");
		Window::CreateWindow(1280, 720, "Lux Tracer");
		Graphics::Init();
		Editor::Init();
	}

	//Update systems
	void Application::Update()
	{
		while (Window::IsOpen())
		{
			Timer::StartFrame((float)glfwGetTime());

			Graphics::Update();
			Editor::Update();
			Window::SwapBuffer();

			Timer::EndFrame((float)glfwGetTime());
		}
	}

	//Release systems
	void Application::UnInit()
	{
		Editor::UnInit();
		Graphics::UnInit();
		Window::TerminateWindow();
	}
}