#include "Utils.h"

#include <iostream>
#include <SDL_opengl.h>

namespace Utils
{
#ifdef _DEBUG
	void Assert(const bool expression, std::string&& message)
	{
		if (!expression)
		{
			std::cout << std::forward<std::string>(message);
			std::abort();
		}
	}
#else
	void Assert(const bool expression, std::string&& message)
	{
		(void)expression;
		(void)message;
	}
#endif // _DEBUG


	void DrawCircle(const MathUtils::Point2f& position, const int radius, const MathUtils::RGBColour& colour) noexcept
	{
		glColor4f(colour.r, colour.g, colour.b, colour.a);
		glBegin(GL_LINES);
		{
			for (int angle{}; angle < 360; ++angle)
				glVertex2d(position.x + cos(angle) * radius, position.y + sin(angle) * radius);
		}
		glEnd();
	}
}