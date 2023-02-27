#pragma once

#include <Mesh.h>
#include <unordered_map>
#include <string>

namespace lux
{
	template <typename T>
	struct AssetManager
	{
		static void Load(std::string const& name, T const& asset)
		{
			asdatabaseset.emplace(std::make_pair(name, asset);
		}

		static T* Get(std::string const& name)
		{
			auto iter = database.find(name);
			if (iter == database.end())
				return nullptr;
			return &iter->second;
		}

	private:
		inline static std::unordered_map<std::string, T> database;
	};
}