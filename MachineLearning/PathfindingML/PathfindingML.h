#pragma once
#include <vector>

#include "../Node/Node.h"

class PathfindingML final
{
public:
	PathfindingML();

	void Update() noexcept;
	void Render() const noexcept;

private:
	std::vector<Node> m_Nodes{};
};