#pragma once

#include "../Math/MathUtils.h"

#include <stdint.h>

class Texture;
class Node final
{
public:
	Node(MathUtils::Point2f&& position, MathUtils::RGBColour&& colour, const uint32_t index);
	~Node();

	Node(const Node& other) noexcept;
	Node(Node&& other) noexcept;
	Node& operator=(const Node& other) noexcept;
	Node& operator=(Node&& other) noexcept;

	void Render() const noexcept;

private:
	MathUtils::Point2f m_Position;
	MathUtils::RGBColour m_Colour;
	uint32_t m_Index;

	Texture* m_pTexture;
};