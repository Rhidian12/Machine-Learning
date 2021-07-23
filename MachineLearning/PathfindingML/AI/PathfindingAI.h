#pragma once
#include "../../Math/MathUtils.h"
#include "../../FMatrix/FMatrix.h"

#include "../../Node/Node.h"
#include "../../Transition/Transition.h"

#include <vector>

class PathfindingAI final
{
public:
	PathfindingAI(const uint32_t amountOfNodes, const uint32_t startLocation, const uint32_t goal);

	bool Train() noexcept;
	const float&& Update() noexcept;

	void SetRewardMatrix(FMatrix&& matrix) noexcept;

	void SetNodes(std::vector<Node*>* const nodes) noexcept;
	void SetTransitions(std::vector<Transition*>* const transitions) noexcept;

private:
	FMatrix m_QMatrix;
	FMatrix m_RewardMatrix;
	uint32_t m_AmountOfNodes;
	uint32_t m_StartLocation;
	uint32_t m_Goal;

	float m_Gamma;

	int m_CurrentIteration;
	int m_NrOfIterations;
	
	std::vector<Node*>* m_pNodes;
	std::vector<Transition*>* m_pTransitions;
};

