#pragma once

#include <Systems/System.h>
#include <pbo.h>

namespace lux
{
	template<typename BaseSystem>
	struct GraphicsSystem : public BaseSystem
	{
		static void Init();
		static void Update();
		static void UnInit();

		inline static Pbo pbo;
	};

	typedef GraphicsSystem<System> Graphics;
}

#include "../../src/Systems/GraphicsSystem.cpp"