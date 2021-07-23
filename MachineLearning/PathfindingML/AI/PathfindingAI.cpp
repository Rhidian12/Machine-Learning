#include "PathfindingAI.h"

PathfindingAI::PathfindingAI(const uint32_t amountOfNodes)
	: m_QMatrix{ amountOfNodes, amountOfNodes }
	, m_RewardMatrix{ amountOfNodes, amountOfNodes }
	, m_AmountOfNodes{ amountOfNodes }
	, m_pNodes{}
	, m_pTransitions{}
{
}

void PathfindingAI::Update() noexcept
{
	// Select a random node (FROM)
	
}

void PathfindingAI::SetRewardMatrix(FMatrix&& matrix) noexcept
{
	m_RewardMatrix = std::forward<FMatrix>(matrix);
}

void PathfindingAI::SetNodes(std::vector<Node>* const pNodes) noexcept
{
	m_pNodes = pNodes;
}

void PathfindingAI::SetTransitions(std::vector<Transition>* const pTransitions) noexcept
{
	m_pTransitions = pTransitions;
}
