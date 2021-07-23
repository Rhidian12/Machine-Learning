#pragma once
#include "../../Math/MathUtils.h"
#include "../../FMatrix/FMatrix.h"

#include "../../Node/Node.h"
#include "../../Transition/Transition.h"

#include <vector>

class PathfindingAI
{
public:
	PathfindingAI(const uint32_t amountOfNodes);

	void Update() noexcept;

	void SetRewardMatrix(FMatrix&& matrix) noexcept;

	void SetNodes(std::vector<Node>* const nodes) noexcept;
	void SetTransitions(std::vector<Transition>* const transitions) noexcept;

private:
	FMatrix m_QMatrix;
	FMatrix m_RewardMatrix;
	uint32_t m_AmountOfNodes;
	
	std::vector<Node*>* m_pNodes;
	std::vector<Transition*>* m_pTransitions;
};

