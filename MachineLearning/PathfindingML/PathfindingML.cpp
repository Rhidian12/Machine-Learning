#include "PathfindingML.h"

PathfindingML::PathfindingML()
{
	m_Nodes.push_back(Node{ MathUtils::Point2f{100.f, 50.f}, MathUtils::RGBColour{192.f, 192.f, 192.f}, 0 });
}

void PathfindingML::Update() noexcept
{
}

void PathfindingML::Render() const noexcept
{
	for (const Node& node : m_Nodes)
		node.Render();
}
