#include "PathfindingAI.h"

PathfindingAI::PathfindingAI(const int amountOfNodes)
	: m_QMatrix{ amountOfNodes, amountOfNodes }
	, m_RewardMatrix{ amountOfNodes, amountOfNodes }
{
}

void PathfindingAI::Update() noexcept
{
}

void PathfindingAI::SetRewardMatrix(FMatrix&& matrix) noexcept
{
	m_RewardMatrix = std::forward<FMatrix>(matrix);
}
