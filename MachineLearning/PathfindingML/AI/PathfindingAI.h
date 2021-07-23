#pragma once
#include "../../Math/MathUtils.h"
#include "../../FMatrix/FMatrix.h"

class PathfindingAI
{
public:
	PathfindingAI(const int amountOfNodes);

	void Update() noexcept;

	void SetRewardMatrix(FMatrix&& matrix) noexcept;

private:
	FMatrix m_QMatrix;
	FMatrix m_RewardMatrix;
};

