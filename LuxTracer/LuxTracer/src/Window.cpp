#include <Window.h>
#include <Logger.h>

namespace lux
{
	int Window::width{};
	int Window::height{};
	GLFWwindow* Window::window{};

	void lux::Window::CreateWindow(int _width, int _height, const char* windowName)
	{
		width = _width;
		height = _height;

		// Create window
		if (!glfwInit()) { lux::LogError("Failed to init GLFW!"); }
		glfwWindowHint(GLFW_SAMPLES, 1); // change for anti-aliasing
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		window = glfwCreateWindow(width, height, "Geometry Toolbox", nullptr, nullptr);
		if (!window) { glfwTerminate(); lux::LogError("Failed to create GLFW window!"); }

		glfwMakeContextCurrent(window);

		// Init glew
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) { glfwTerminate(); lux::LogError("Failed to init GLEW!"); }
	}

	void Window::TerminateWindow()
	{
		glfwTerminate();
	}

	GLFWwindow* Window::GetWindow()
	{
		return window;
	}
}