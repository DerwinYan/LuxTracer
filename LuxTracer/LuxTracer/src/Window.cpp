#include <Window.h>
#include <Logger.h>

namespace lux
{
	int Window::width{};
	int Window::height{};
	GLFWwindow* Window::windowptr{};

	void Window::CreateWindow(int const _width, int const _height, char const* name)
	{
		width = _width;
		height = _height;

		// Create window
		if (!glfwInit()) { lux::LogError("Failed to init GLFW!"); }
		glfwWindowHint(GLFW_SAMPLES, 1); // change for anti-aliasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		windowptr = glfwCreateWindow(width, height, name, nullptr, nullptr);
		if (!windowptr) { glfwTerminate(); lux::LogError("Failed to create GLFW window!"); }

		glfwMakeContextCurrent(windowptr);
		glfwSwapInterval(0);

		// Init glew
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) { glfwTerminate(); lux::LogError("Failed to init GLEW!"); }
	}

	bool Window::IsOpen()
	{
		glfwPollEvents();
		return !glfwWindowShouldClose(windowptr);
	}

	void Window::SwapBuffer()
	{
		glfwSwapBuffers(windowptr);
	}

	void Window::TerminateWindow()
	{
		glfwTerminate();
	}
}