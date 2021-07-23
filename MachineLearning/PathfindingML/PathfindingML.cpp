#include "PathfindingML.h"

#include "../Texture/Texture.h"
#include "../Renderer/Renderer.h"

PathfindingML::PathfindingML()
	: m_AI{ 0 } /*I'm lazy TODO: Make this better, lazy bastard*/
{
	m_Nodes.push_back(std::move(Node{ MathUtils::Point2f{200.f, 100.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 0, 0.f }));
	m_Nodes.push_back(std::move(Node{ MathUtils::Point2f{300.f, 150.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 1, 40.f }));
	m_Nodes.push_back(std::move(Node{ MathUtils::Point2f{100.f, 150.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 2, 0.f }));
	m_Nodes.push_back(std::move(Node{ MathUtils::Point2f{300.f, 250.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 3, 80.f }));
	m_Nodes.push_back(std::move(Node{ MathUtils::Point2f{300.f, 350.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 4, 100.f }));
	m_Nodes.push_back(std::move(Node{ MathUtils::Point2f{100.f, 250.f}, MathUtils::RGBColour{100.f, 100.f, 100.f}, 5, 0.f }));

	m_Transitions.push_back(std::move(Transition{ &m_Nodes[0], &m_Nodes[1] }));
	m_Transitions.push_back(std::move(Transition{ &m_Nodes[0], &m_Nodes[2] }));
	m_Transitions.push_back(std::move(Transition{ &m_Nodes[2], &m_Nodes[5] }));
	m_Transitions.push_back(std::move(Transition{ &m_Nodes[3], &m_Nodes[4] }));
	m_Transitions.push_back(std::move(Transition{ &m_Nodes[1], &m_Nodes[3] }));

	m_AI = PathfindingAI{ static_cast<int>(m_Nodes.size()) };

	FMatrix rewardMatrix{ m_Nodes.size(),m_Nodes.size() };
}

void PathfindingML::Update() noexcept
{
}

void PathfindingML::Render() const noexcept
{
	for (const Node& node : m_Nodes)
		node.Render();

	for (const Transition& transition : m_Transitions)
		transition.Render();
}
