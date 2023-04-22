#pragma once

#include <Systems/System.h>

namespace lux
{
	template<typename BaseSystem>
	struct SceneManagerSystem : public BaseSystem
	{
		static void CreateGO()
		{

		}

		static void DestroyGO();

	};

	typedef SceneManagerSystem<System> SceneManager;
}