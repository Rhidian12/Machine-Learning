#pragma once
#include <string> // std::string

namespace Utils
{
	void Assert(const bool expression, std::string&& message);
}