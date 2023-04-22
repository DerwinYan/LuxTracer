#pragma once

#include <vector>
#include <GameObject.h>

namespace lux
{
	struct System
	{
		inline static std::vector<GameObject> scene{};
	};
}