#include "DinoAI.h"
#include "../Dino/Dino.h"

#include <algorithm>

#include <SDL.h>

#include <iostream>

DinoAI::DinoAI(Dino* const pDino, const uint32_t windowWidth)
	: m_pDino{ pDino }
	, m_Cacti{}
	, m_WindowWidth{ windowWidth }
	, m_CurrentIteration{}
	, m_IsAITraining{ true }
	, m_WasCactusRemoved{}
	, m_Brain{ 3,1 }
	, m_Inputs{ 5,1 }
{
}

void DinoAI::GameUpdate(const std::vector<Cactus>& cacti) noexcept
{
	for (const Cactus& cactus : cacti)
		if (IsCactusInScreen(cactus))
			AddCactus(cactus);

	RemoveCacti();
}

void DinoAI::UpdateAI(const float speed, const float score) noexcept
{
	/*
	* The AI can view the Dino
	* The AI can jump with the Dino
	* The AI can view all cacti ON SCREEN
	* The AI can view the width of all cacti ON SCREEN
	* The AI knows the speed of the world
	*/

	// m_Brain{ 3,1 }
	/*
	*  [0][0] == Staying Alive Grants Points
	*  [1][0] == Passing a Cactus Grants Points
	*  [2][0] == If we jump over a cactus but die shortly after, this decreases
	*/

	// m_Inputs{ 5,1 }
	/*
	*  [0][0] == Dino Jump Distance
	*  [1][0] == Nearest Cactus Width
	*  [2][0] == Dino Distance From Nearest Cactus
	*  [3][0] == Dino Distance From Second Cactus
	*  [4][0] == World Speed
	*/

	// == First Update The AI's Inputs (Senses if you will) == 
	UpdateInputs(speed);

	// == Make The AI Select An Action ==

	m_Brain.IncreaseValueOfCell(0, 0, score);

	if (m_WasCactusRemoved) // we got past a cactus
	{
		m_WasCactusRemoved = false; // reset the dirty flag

		m_Brain.IncreaseValueOfCell(1, 0, 100.f); // increase Cactus Jumping Score
	}
}

void DinoAI::Train(const float speed, const float score) noexcept
{
	if (!SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE])
	{
		UpdateAI(speed, score);
	}
	else
	{
		m_IsAITraining = false;
		
		if (m_CurrentIteration % 10 == 0)
			std::cout << "Current iteration: " << m_CurrentIteration << std::endl;
	}
}

void DinoAI::Reset() noexcept
{
	/*
	*  [0][0] == Staying Alive Grants Points => Dying loses points
	*  [1][0] == Passing a Cactus Grants Points => Dying loses points
	*  [2][0] == If we jump over a cactus but die shortly after, this decreases => Dying within 1sec after jumping over a cactus loses points
	*/

	const float pointLossRatio{ 0.25f };

	m_Brain.IncreaseValueOfCell(0, 0, -m_Brain.Get(0, 0) * pointLossRatio);
	m_Brain.IncreaseValueOfCell(1, 0, -m_Brain.Get(1, 0) * pointLossRatio);

	// TODO, do [2][0]

	++m_CurrentIteration;
}

const bool DinoAI::GetIsAITraining() const noexcept
{
	return m_IsAITraining;
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
		{
			it = m_Cacti.erase(it);
			m_WasCactusRemoved = true;
		}
		else
			++it;
	}
}

void DinoAI::UpdateInputs(const float speed) noexcept
{
	// m_Inputs{ 5,1 }
	/*
	*  [0][0] == Dino Jump Distance
	*  [1][0] == Nearest Cactus Width
	*  [2][0] == Dino Distance From Nearest Cactus
	*  [3][0] == Dino Distance From Second Cactus
	*  [4][0] == World Speed
	*/

	// == Update m_Inputs Dino Jump Distance ==
	const float totalTime{ m_pDino->GetJumpSpeed() / m_pDino->GetGravity() * 2.f }; // velocity / gravity * 2.f == total time a jump takes
	const float distance{ totalTime * speed };
	m_Inputs.Set(0, 0, distance);

	// == Update m_Inputs Nearest Cactus Width ==
	if (m_Cacti.empty())
		m_Inputs.Set(1, 0, -1.f); // if there are no cacti, set the width to something invalid (-1.f)
	else
		m_Inputs.Set(1, 0, m_Cacti.front().GetAvatar().width);

	// == Update m_Inputs Dino Distance From Nearest Cactus ==
	if (m_Cacti.empty())
		m_Inputs.Set(2, 0, -1.f); // there is no cactus, so set it to something invalid (-1.f)
	else
		m_Inputs.Set(2, 0, MathUtils::Magnitude(MathUtils::Vector2f{ m_pDino->GetAvatar().leftBottom - m_Cacti.front().GetAvatar().leftBottom }));

	// == Update m_Inputs Dino Distance From Second Cactus ==
	if (m_Cacti.size() < 2)
		m_Inputs.Set(3, 0, -1.f); // there is no second cactus, so set it to something invalid (-1.f)
	else
		m_Inputs.Set(3, 0, MathUtils::Magnitude(MathUtils::Vector2f{ m_pDino->GetAvatar().leftBottom - m_Cacti[1].GetAvatar().leftBottom }));

	// == Update m_Inputs World Speed ==
	m_Inputs.Set(4, 0, speed);
}

void DinoAI::SelectAction() noexcept
{
	// m_Brain{ 3,1 }
	/*
	*  [0][0] == Staying Alive Grants Points
	*  [1][0] == Passing a Cactus Grants Points
	*  [2][0] == If we jump over a cactus but die shortly after, this decreases
	*/

	// m_Inputs{ 5,1 }
	/*
	*  [0][0] == Dino Jump Distance
	*  [1][0] == Nearest Cactus Width
	*  [2][0] == Dino Distance From Nearest Cactus
	*  [3][0] == Dino Distance From Second Cactus
	*  [4][0] == World Speed
	*/

	/*
	* Now, based on the inputs and experience from the m_Brain, we need to decide when to jump
	* 
	*/
}
