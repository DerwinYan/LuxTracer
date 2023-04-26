#pragma once

#include <Systems/System.h>

namespace lux
{
	template<typename BaseSystem>
	struct SceneManagerSystem : public BaseSystem
	{
		static void CreateGO(math::vec3 const& pos, float const radius, Material const& mat)
		{
			BaseSystem::scene.emplace_back(GameObject{ pos, radius, mat });
		}

		//static void DestroyGO();

	};

	typedef SceneManagerSystem<System> SceneManager;
}