#pragma once

#include <string>
#include <source_location>

namespace lux
{
	void LogMsg(std::string_view const& msg);

	void LogError(
		std::string_view const& msg, 
		std::source_location const& location = std::source_location::current());

	void LogAssert(
		bool condition, 
		std::string_view const& msg,
		std::source_location const& location = std::source_location::current());
}