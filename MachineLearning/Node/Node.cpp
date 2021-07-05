#include "Node.h"
#include "../Utils/Utils.h"

Node::Node(MathUtils::Point2f&& position, MathUtils::RGBColour&& colour, const uint32_t index)
	: m_Position{ position }
	, m_Colour{ colour }
	, m_Index{ index }
{
}

void Node::Render() const noexcept
{
	Utils::DrawCircle(m_Position, 10, MathUtils::RGBColour{ 192.f, 192.f, 192.f });
}
