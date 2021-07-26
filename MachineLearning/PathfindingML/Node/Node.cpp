#include "Node.h"
#include "../../Utils/Utils.h"
#include "../../Texture/Texture.h"
#include "../../Renderer/Renderer.h"
#include "../Transition/Transition.h"

Node::Node(MathUtils::Point2f position, MathUtils::RGBColour colour, const uint32_t index)
	: m_Position{ position }
	, m_Colour{ colour }
	, m_Index{ index }
	, m_pTexture{}
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
	, m_pTransitions{ other.m_pTransitions }
{
}

Node::Node(Node&& other) noexcept
	: m_Position{ std::move(other.m_Position) }
	, m_Colour{ std::move(other.m_Colour) }
	, m_Index{ std::move(other.m_Index) }
	, m_pTexture{ std::move(other.m_pTexture) }
	, m_pTransitions{ std::move(other.m_pTransitions) }
{
	other.m_pTransitions.clear();
	other.m_pTexture = nullptr;
}

Node& Node::operator=(const Node& other) noexcept
{
	m_Position = other.m_Position;
	m_Colour = other.m_Colour;
	m_Index = other.m_Index;
	m_pTexture = other.m_pTexture;
	m_pTransitions = other.m_pTransitions;
	return *this;
}

Node& Node::operator=(Node&& other) noexcept
{
	m_Position = std::move(other.m_Position);
	m_Colour = std::move(other.m_Colour);
	m_Index = std::move(other.m_Index);
	m_pTexture = std::move(other.m_pTexture);
	m_pTransitions = std::move(other.m_pTransitions);
	other.m_pTransitions.clear();
	other.m_pTexture = nullptr;
	return *this;
}

#include <iostream>
void Node::Render() const noexcept
{
	using namespace MathUtils;

	const int radius{ 10 };
	Utils::DrawCircle(m_Position, radius, m_Colour);
	Renderer::GetInstance()->Render(m_pTexture, MathUtils::Point2f{ m_Position.x, m_Position.y + m_pTexture->GetHeight() / 2.f });

	for (Transition* const pTransition : m_pTransitions)
	{
		if (!pTransition->GetIsRendered())
		{
			pTransition->Render(radius);
			pTransition->SetIsRendered(true);
		}
	}
}

void Node::AddTransition(Transition* const pTransition) noexcept
{
	const std::vector<Transition*>::const_iterator cIt = std::find(m_pTransitions.cbegin(), m_pTransitions.cend(), pTransition);

	if (cIt == m_pTransitions.cend())
		m_pTransitions.push_back(pTransition);
}

const std::vector<Transition*>& Node::GetTransitions() const noexcept
{
	return m_pTransitions;
}

const MathUtils::Point2f& Node::GetPosition() const noexcept
{
	return m_Position;
}

const uint32_t Node::GetIndex() const noexcept
{
	return m_Index;
}
