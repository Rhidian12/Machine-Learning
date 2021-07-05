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
	m_pTexture = new Texture{ "Data/OswaldLight.ttf", std::to_string(index), 5, m_Colour };
}

Node::~Node()
{
	Utils::SafeDelete(m_pTexture);
}

Node::Node(const Node& other) noexcept
	: m_Position{ other.m_Position }
	, m_Colour{ other.m_Colour }
	, m_Index{ other.m_Index }
	, m_pTexture{ other.m_pTexture }
{
}

Node::Node(Node&& other) noexcept
	: m_Position{ std::move(other.m_Position) }
	, m_Colour{ std::move(other.m_Colour) }
	, m_Index{ std::move(other.m_Index) }
	, m_pTexture{ std::move(other.m_pTexture) }
{
	other.m_pTexture = nullptr;
}

Node& Node::operator=(const Node& other) noexcept
{
	m_Position = other.m_Position;
	m_Colour = other.m_Colour;
	m_Index = other.m_Index;
	m_pTexture = other.m_pTexture;
	return *this;
}

Node& Node::operator=(Node&& other) noexcept
{
	m_Position = std::move(other.m_Position);
	m_Colour = std::move(other.m_Colour);
	m_Index = std::move(other.m_Index);
	m_pTexture = std::move(other.m_pTexture);
	other.m_pTexture = nullptr;
	return *this;
}

void Node::Render() const noexcept
{
	Utils::DrawCircle(m_Position, 10, m_Colour);
	Renderer::GetInstance()->Render(m_pTexture, MathUtils::Point2f{ m_Position.x + 5.f, m_Position.y + 5.f });
}
