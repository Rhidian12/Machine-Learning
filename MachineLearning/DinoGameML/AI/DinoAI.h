#pragma once

#include "../Cactus/Cactus.h"
#include "../../FMatrix/FMatrix.h"

#include <vector>

class Dino;

class DinoAI final
{
public:
	DinoAI(Dino* const pDino, const uint32_t windowWidth);

	void GameUpdate(const std::vector<Cactus>& cacti) noexcept;

	void UpdateAI(const float speed, const float score) noexcept;
	void Train(const float speed, const float score) noexcept;

	void Reset() noexcept;

	const bool GetIsAITraining() const noexcept;

private:
	bool IsCactusInScreen(const Cactus& cactus) const noexcept;
	void AddCactus(const Cactus& cactus) noexcept;
	void RemoveCacti() noexcept;
	void UpdateInputs(const float speed) noexcept;
	void SelectAction() noexcept;

	Dino* m_pDino;
	std::vector<Cactus> m_Cacti;

	uint32_t m_WindowWidth;

	int m_CurrentIteration;
	bool m_IsAITraining;

	bool m_WasCactusRemoved;

	FMatrix m_Brain;
	FMatrix m_Inputs;
};