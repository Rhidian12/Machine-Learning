#include "Node.h"
#include "../Utils/Utils.h"
#include "../Texture/Texture.h"
#include "../Renderer/Renderer.h"

Node::Node(MathUtils::Point2f&& position, MathUtils::RGBColour&& colour, const uint32_t index, const float score)
	: m_Position{ position }
	, m_Colour{ colour }
	, m_Index{ index }
	, m_pTexture{}
	, m_Score{ score }
	, m_pTransitions{}
{
	m_pTexture = new Texture{ "Data/OswaldLight.ttf", std::to_string(index), 15, m_Colour };
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
	Renderer::GetInstance()->Render(m_pTexture, MathUtils::Point2f{ m_Position.x, m_Position.y + m_pTexture->GetHeight() / 2.f });
}

void Node::AddTransition(Transition* const pTransition) noexcept
{
	m_pTransitions.insert(pTransition);
}

const std::unordered_set<Transition*>& Node::GetTransitions() const noexcept
{
	return m_pTransitions;
}

const MathUtils::Point2f& Node::GetPosition() const noexcept
{
	return m_Position;
}

const float Node::GetScore() const noexcept
{
	return m_Score;
}
