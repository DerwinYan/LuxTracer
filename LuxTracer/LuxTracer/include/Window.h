#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lux
{
	struct Window
	{
	public:
		static void CreateWindow(int width, int height, const char* windowName);
		static void TerminateWindow();
		static GLFWwindow* GetWindow();

	public:
		static int width;
		static int height;
		static GLFWwindow* window;
	};
}