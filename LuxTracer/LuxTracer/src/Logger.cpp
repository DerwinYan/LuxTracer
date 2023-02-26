#include "Logger.h"
#include <iostream>
#undef NDEBUG
#include <cassert>
#define NDEBUG

namespace lux
{
	void LogMsg(std::string_view const& msg)
	{
		std::cout << msg << '\n';
	}

	void LogError(std::string_view const& msg, std::source_location const& location)
	{
		std::cout << "[ERROR]\n";
		std::cout << "File: " << location.file_name() << ": " << location.line() << '\n';
		std::cout << "Message: " << msg << '\n';
		assert(0);
	}

	void LogAssert(bool condition, std::string_view const& msg, std::source_location const& location)
	{
		if (!condition)
		{
			LogError(msg, location);
			assert(condition);
		}
	}
}