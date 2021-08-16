#pragma once

#include "../Cactus/Cactus.h"

#include <vector>

class Dino;

class DinoAI final
{
public:
	DinoAI(Dino* const pDino, const uint32_t windowWidth);

	void GameUpdate(const std::vector<Cactus>& cacti) noexcept;

	void UpdateAI() noexcept;
	void Train() noexcept;

private:
	bool IsCactusInScreen(const Cactus& cactus) const noexcept;
	void AddCactus(const Cactus& cactus) noexcept;
	void RemoveCacti() noexcept;

	Dino* m_pDino;
	std::vector<Cactus> m_Cacti;

	uint32_t m_WindowWidth;

	int m_CurrentIteration;
};