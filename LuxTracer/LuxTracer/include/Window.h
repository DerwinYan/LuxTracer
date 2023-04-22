#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lux
{
	struct Window
	{
		static void CreateWindow(int const width, int const height, char const* name);
		static bool IsOpen();
		static void SwapBuffer();
		static void TerminateWindow();

		static int width;
		static int height;
		static GLFWwindow* windowptr;
	};
}
