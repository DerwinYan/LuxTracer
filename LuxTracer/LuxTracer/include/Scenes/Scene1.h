#pragma once

#include <Systems/SceneManagerSystem.h>

namespace lux::scene
{
	static void LoadScene1()
	{
		//Light
		SceneManager::CreateGO({ 0.0f, 0.44f, -0.26f }, 0.2f, Material(math::vec3(0.0f, 0.0f, 0.0f), {1.0f, 0.9f, 0.7f}, 1.0f));
		
		//Red ball
		SceneManager::CreateGO({ -1.25f, 0.0f, -1.5f }, 0.5f, Material(math::vec3(0.965f, 0.258f, 0.258f)));

		//Green ball
		SceneManager::CreateGO({ 0.0f, 0.0f, -1.5f }, 0.5f, Material(math::vec3(0.1f, 0.94f, 0.223f)));
		
		//Blue ball
		SceneManager::CreateGO({ 1.25f, 0.0f, -1.5f }, 0.5f, Material(math::vec3(0.404f, 0.07f, 0.956f)));
		
		//Floor ball
		SceneManager::CreateGO({ 0.0f,-100.5f, -1.0f }, 100.0f, Material(math::vec3(205.0f/255.0f, 210.0f/255.0f, 182.0f/255.0f), math::vec3(205.0f / 255.0f, 210.0f / 255.0f, 182.0f / 255.0f), 0.6f));
	}
}