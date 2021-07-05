#include "PathfindingML.h"

PathfindingML::PathfindingML()
{
	m_Nodes.push_back(std::move(Node{ MathUtils::Point2f{100.f, 50.f}, MathUtils::RGBColour{210.f, 210.f, 210.f}, 0 }));
}

void PathfindingML::Update() noexcept
{
}

void PathfindingML::Render() const noexcept
{
	for (const Node& node : m_Nodes)
		node.Render();
}
