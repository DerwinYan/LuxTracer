#pragma once

#include <Systems/System.h>

namespace lux
{
	template<typename BaseSystem>
	struct SceneManagerSystem : public BaseSystem
	{
		static void CreateGO(math::dvec3 const& pos, double const radius)
		{
			BaseSystem::scene.emplace_back(GameObject { pos, radius });
		}

		//static void DestroyGO();

	};

	typedef SceneManagerSystem<System> SceneManager;
}