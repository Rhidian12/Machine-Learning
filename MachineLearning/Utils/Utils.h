#pragma once
#include <string> // std::string

#include "../Math/MathUtils.h"

namespace Utils
{
	void Assert(const bool expression, std::string&& message);

	void DrawCircle(const MathUtils::Point2f& position, const int radius, const MathUtils::RGBColour& colour) noexcept;
}