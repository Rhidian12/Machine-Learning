#pragma once

#include "../Math/MathUtils.h"

#include <stdint.h>

class Node final
{
public:
	Node(MathUtils::Point2f&& position, MathUtils::RGBColour&& colour, const uint32_t index);

	void Render() const noexcept;

private:
	MathUtils::Point2f m_Position;
	MathUtils::RGBColour m_Colour;
	uint32_t m_Index;
};