#pragma once

#include <Systems/System.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <Window.h>

namespace lux
{
	template<typename BaseSystem>
	struct EditorSystem : public BaseSystem
	{
		static void Init();
		static void Update();
		static void UnInit();
	};

	typedef EditorSystem<System> Editor;
}

#include "../../src/Systems/EditorSystem.cpp"