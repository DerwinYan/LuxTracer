#pragma once

#include <Systems/SceneManagerSystem.h>

namespace lux::scene
{
	static void LoadScene1()
	{
		SceneManager::CreateGO({ 0.0f, 0.0f, -1.0f }, 0.5f, Material(math::vec3(1.0f, 0.0f, 0.0f)));
		SceneManager::CreateGO({ 0.0f,-100.5f, -1.0f }, 100.0f, Material(math::vec3(0.0f, 1.0f, 0.0f)));
	}
}