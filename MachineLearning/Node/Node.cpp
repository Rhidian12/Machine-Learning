#include "Node.h"
#include "../Utils/Utils.h"
#include "../Texture/Texture.h"
#include "../Renderer/Renderer.h"

Node::Node(MathUtils::Point2f&& position, MathUtils::RGBColour&& colour, const uint32_t index)
	: m_Position{ position }
	, m_Colour{ colour }
	, m_Index{ index }
	, m_pTexture{}
{
	m_pTexture = new Texture{ "../Data/Oswald-Light.ttf", std::to_string(index), 5, m_Colour };
}

void Node::Render() const noexcept
{
	Utils::DrawCircle(m_Position, 10, m_Colour);
	Renderer::GetInstance()->Render(m_pTexture, MathUtils::Point2f{ m_Position.x + 5.f, m_Position.y + 5.f });
}
