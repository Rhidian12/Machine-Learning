#include "Utils.h"
#include "../Renderer/Renderer.h"

#include <iostream>
#include <SDL.h>

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


	void DrawCircle(const MathUtils::Point2f& position, const int radius, const MathUtils::RGBColour& colour, const float angleToDraw) noexcept
	{
		const float newY{};
		SDL_Renderer* const pSDLRenderer{ Renderer::GetInstance()->GetSDLRenderer() };
		SDL_SetRenderDrawColor(pSDLRenderer, Uint8(colour.r), Uint8(colour.g), Uint8(colour.b), Uint8(colour.a));
			for (float angle{}; angle < angleToDraw; ++angle)
				SDL_RenderDrawPointF(pSDLRenderer, float(position.x + cos(angle) * radius), float(position.y + sin(angle) * radius));
	}
}