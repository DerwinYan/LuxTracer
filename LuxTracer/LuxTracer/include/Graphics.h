#pragma once
#include <PboRenderer.h>

namespace lux
{
	class GraphicSystem
	{
	public:
		static void Init();
		static void Update();
		static void UnInit();

	private:
		inline static PboRenderer pboRenderer;
	};
};