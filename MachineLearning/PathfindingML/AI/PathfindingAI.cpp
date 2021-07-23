#include "PathfindingAI.h"

#include <iostream>

PathfindingAI::PathfindingAI(const uint32_t amountOfNodes, const uint32_t startLocation, const uint32_t goal)
	: m_QMatrix{ amountOfNodes, amountOfNodes }
	, m_RewardMatrix{ amountOfNodes, amountOfNodes }
	, m_AmountOfNodes{ amountOfNodes }
	, m_pNodes{}
	, m_pTransitions{}
	, m_Gamma{ 0.8f }
	, m_CurrentIteration{}
	, m_NrOfIterations{ 700 } /* arbitrary number */
	, m_StartLocation{ startLocation }
	, m_Goal{ goal }
{
}

bool PathfindingAI::Train() noexcept
{
	if (m_CurrentIteration < m_NrOfIterations) // we are still training
	{
		const float score{ Update() };

		std::cout << "Iteration: " << m_CurrentIteration++ << ", Score: " << score << std::endl;

		return true;
	}
	else // end of training
	{
		// print Q matrix
		std::cout << "QMatrix:" << std::endl;
		m_QMatrix.Print();
		std::cout << std::endl;

		uint32_t location{ m_StartLocation };

		std::cout << "We start at index: " << location << std::endl;

		while (location != m_Goal)
		{
			const float maxOfRow{ m_QMatrix.GetMaxOfRow(location) };

			std::vector<uint32_t> columnIndices{};

			for (uint32_t c{}; c < m_QMatrix.GetNumberOfColumns(); ++c)
				if (m_QMatrix.Get(location, c) == maxOfRow)
					columnIndices.push_back(c);

			location = columnIndices[rand() % columnIndices.size()];
			
			std::cout << location << "\t";
		}

		std::cout << std::endl;
		++m_CurrentIteration;

		return false;
	}
}

const float&& PathfindingAI::Update() noexcept
{
	// Select a random node (FROM)
	const Node& fromNode{ (*m_pNodes)[rand() % m_pNodes->size()] };

	// select a valid TO node
	const Node& toNode{ *fromNode.GetTransitions()[rand() % fromNode.GetTransitions().size()]->GetToNode() };

	// Calculate the max of row nr [TO NODE INDEX]
	float max{};
	for (size_t i{}; i < m_QMatrix.GetNumberOfColumns(); ++i)
		max += m_QMatrix.Get(toNode.GetIndex(), i);

	// Gather all the columns that have a value equal to max
	std::vector<uint32_t> columnIndices{};
	for (size_t i{}; i < m_QMatrix.GetNumberOfColumns(); ++i)
		if (m_QMatrix.Get(toNode.GetIndex(), i) == max)
			columnIndices.push_back(i);

	// Get the value from the random cell
	const float randomValueFromQMatrix{ m_QMatrix.Get(toNode.GetIndex(), columnIndices[rand() % columnIndices.size()]) };

	// Update the value for the Q matrix
	const float qUpdate{ m_RewardMatrix.Get(fromNode.GetIndex(), toNode.GetIndex()) + m_Gamma * randomValueFromQMatrix };
	m_QMatrix.Set(fromNode.GetIndex(), toNode.GetIndex(), qUpdate);

	return std::move(100.f * m_QMatrix.GetSum() / m_QMatrix.GetMax());
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
