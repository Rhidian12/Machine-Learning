#include "Utils.h"
#include <iostream>

namespace Utils
{
	void Assert(const bool expression, std::string&& message)
	{
		if (!expression)
		{
			std::cout << std::forward<std::string>(message);
			std::abort();
		}
	}
}