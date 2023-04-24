#pragma once

#include <Systems/SceneManagerSystem.h>

namespace lux::scene
{
	static void LoadScene1()
	{
		SceneManager::CreateGO({ 0.0, 0.0, -1.0 }, 0.5);
		SceneManager::CreateGO({ 0.0,-100.5,-1.0 }, 100.0);
	}
}