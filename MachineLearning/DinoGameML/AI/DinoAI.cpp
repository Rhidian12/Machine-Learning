#include "DinoAI.h"

#include <algorithm>

#include <SDL.h>

DinoAI::DinoAI(Dino* const pDino, const uint32_t windowWidth)
	: m_pDino{ pDino }
	, m_Cacti{}
	, m_WindowWidth{ windowWidth }
	, m_CurrentIteration{}
{
}

/*
* The AI can view the Dino
* The AI can jump with the Dino
* The AI can view all cacti ON SCREEN
*/

void DinoAI::GameUpdate(const std::vector<Cactus>& cacti) noexcept
{
	for (const Cactus& cactus : cacti)
		if (IsCactusInScreen(cactus))
			AddCactus(cactus);

	RemoveCacti();
}

void DinoAI::UpdateAI() noexcept
{
}

void DinoAI::Train() noexcept
{
	if (!SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE])
	{
		UpdateAI();
	}
}

bool DinoAI::IsCactusInScreen(const Cactus& cactus) const noexcept
{
	return cactus.GetAvatar().leftBottom.x < m_WindowWidth;
}

void DinoAI::AddCactus(const Cactus& cactus) noexcept
{
	std::vector<Cactus>::const_iterator cIt{ std::find_if(m_Cacti.cbegin(), m_Cacti.cend(), [cactus](const Cactus& c)
		{
			return cactus.GetAvatar() == c.GetAvatar();
		}) };

	if (cIt != m_Cacti.cend())
		m_Cacti.push_back(*cIt);
}

void DinoAI::RemoveCacti() noexcept
{
	for (std::vector<Cactus>::iterator it{ m_Cacti.begin() }; it != m_Cacti.end();)
	{
		if (it->GetAvatar().leftBottom.x < 0.f)
			it = m_Cacti.erase(it);
		else
			++it;
	}
}
