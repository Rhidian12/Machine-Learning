#pragma once
#include <vector>

#include "../Node/Node.h"
#include "../FMatrix/FMatrix.h"
#include "../Transition/Transition.h"
#include "AI/PathfindingAI.h"

class PathfindingML final
{
public:
	PathfindingML();

	bool Update() noexcept;
	void Render() const noexcept;

private:
	std::vector<Node> m_Nodes{};
	std::vector<Transition> m_Transitions{};

	PathfindingAI m_AI;
};