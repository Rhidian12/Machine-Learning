#pragma once
#include <vector>

#include "../Node/Node.h"
#include "../FMatrix/FMatrix.h"
#include "../Transition/Transition.h"

class PathfindingML final
{
public:
	PathfindingML();

	void Update() noexcept;
	void Render() const noexcept;

private:
	std::vector<Node> m_Nodes{};
	std::vector<Transition> m_Transitions{};
};