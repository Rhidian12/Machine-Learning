#include "Utils.h"

#include <iostream>
#include <SDL_opengl.h>

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

	void DrawCircle(const MathUtils::Point2f& position, const int radius, const MathUtils::RGBColour& colour) noexcept
	{
		glBegin(GL_LINES);
		{
			for (int angle{}; angle < 360; ++angle)
				glVertex2d(position.x + cos(angle) * radius, position.y + sin(angle) * radius);
		}
		glEnd();
	}
}