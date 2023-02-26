
#include <Application.h>
#include <Window.h>
#include <Timer.h>
#include <Logger.h>
#include <Graphics.h>
#include <iostream>

int const		windowWidth{ 1280 };
int const		windowHeight{ 720 };
const char* windowName{ "Lux tracer" };

namespace lux
{
	void Application::Init()
	{
		//Initialize systems and load scene
		Window::CreateWindow(windowWidth, windowHeight, windowName);
		GraphicSystem::Init();
	}

	void Application::Run()
	{
		GLFWwindow* window{ Window::GetWindow() };
		while (!glfwWindowShouldClose(window))
		{
			double startTime{ glfwGetTime() };
			glfwPollEvents();
			if (glfwGetKey(window, GLFW_KEY_ESCAPE)) break;

			GraphicSystem::Update();

			glfwSwapBuffers(window);
			glfwSetWindowTitle(window, std::to_string(1000.0 / Time::dt).c_str());

			Time::dt = glfwGetTime() - startTime;
			Time::totalElasped = glfwGetTime();
		}
	}

	void Application::UnInit()
	{
		//Uninit 
		GraphicSystem::UnInit();
		Window::TerminateWindow();
	}
}