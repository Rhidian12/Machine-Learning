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
		const MathUtils::Point2f newPos{ MathUtils::ConvertToBottomLeftOrigin{}(position) };
		SDL_Renderer* const pSDLRenderer{ Renderer::GetInstance()->GetSDLRenderer() };
		SDL_SetRenderDrawColor(pSDLRenderer, Uint8(colour.r), Uint8(colour.g), Uint8(colour.b), Uint8(colour.a));
		for (float angle{}; angle < angleToDraw; ++angle)
			SDL_RenderDrawPoint(pSDLRenderer, int(newPos.x + cos(angle) * radius), int(newPos.y + sin(angle) * radius));
	}

	void DrawLine(const MathUtils::Point2f& startPos, const MathUtils::Point2f& endPos, const MathUtils::RGBColour& colour) noexcept
	{
		const MathUtils::Point2f newStartPos{ MathUtils::ConvertToBottomLeftOrigin{}(startPos) };
		const MathUtils::Point2f newEndPos{ MathUtils::ConvertToBottomLeftOrigin{}(endPos) };

		SDL_Renderer* const pSDLRenderer{ Renderer::GetInstance()->GetSDLRenderer() };
		SDL_SetRenderDrawColor(pSDLRenderer, Uint8(colour.r), Uint8(colour.g), Uint8(colour.b), Uint8(colour.a));

		SDL_RenderDrawLine(pSDLRenderer, int(newStartPos.x), int(newStartPos.y), int(newEndPos.x), int(newEndPos.y));
	}
}