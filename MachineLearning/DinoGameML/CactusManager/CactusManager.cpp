#include "CactusManager.h"
#include "../Dino/Dino.h"

CactusManager::CactusManager(Dino* const pDino, const float cactusY)
	: m_pDino{ pDino }
	, m_Cacti{}
	, m_CactusY{ cactusY }
{
}

void CactusManager::Render() const noexcept
{
	for (const Cactus& cactus : m_Cacti)
		cactus.Render();
}

void CactusManager::Update(const MathUtils::Point2f& cameraLeftBottom, const MathUtils::Point2f& cameraRightBottom) noexcept
{
	if (m_Cacti.size() < 3)
		SpawnCactus(cameraRightBottom);

	RemoveCacti(cameraLeftBottom);
}

const std::vector<Cactus>& CactusManager::GetCacti() const noexcept
{
	return m_Cacti;
}

void CactusManager::SpawnCactus(const MathUtils::Point2f& cameraRightBottom) noexcept
{
	// the minimum distance between cacti needs to be [Dino Current Speed] + [Time from Jump => Ground] + Offset?
	// the maximum distance can be this distance * [number]

	// (m / s) / (m / s^2) <==> (m/s) * (s^2 / m) <==> (s^2*m) / (s * m) = s
	const float totalTime{ m_pDino->GetJumpSpeed() / m_pDino->GetGravity() * 2.f }; // velocity / gravity * 2.f == total time a jump takes

	const float minDistance{ m_pDino->GetSpeed() * totalTime };
	const float maxDistance{ minDistance * 1.5f };

	if (m_Cacti.empty())
	{
		if (MathUtils::RandomNumber(0, 2) % 2 == 0)
			m_Cacti.push_back(Cactus{ MathUtils::Point2f{cameraRightBottom.x, m_CactusY}, true });
		else
			m_Cacti.push_back(Cactus{ MathUtils::Point2f{cameraRightBottom.x, m_CactusY}, false });
	}
	else
	{
		const float randomX{ MathUtils::RandomNumber(minDistance + m_Cacti.back().GetAvatar().leftBottom.x, m_Cacti.back().GetAvatar().leftBottom.x + maxDistance) };

		if (MathUtils::RandomNumber(0, 2) % 2 == 0)
			m_Cacti.push_back(Cactus{ MathUtils::Point2f{m_Cacti.back().GetAvatar().leftBottom.x + randomX, m_CactusY}, true });
		else
			m_Cacti.push_back(Cactus{ MathUtils::Point2f{m_Cacti.back().GetAvatar().leftBottom.x + randomX, m_CactusY}, false });
	}
}

void CactusManager::RemoveCacti(const MathUtils::Point2f& leftBottom) noexcept
{
	for (std::vector<Cactus>::iterator it{ m_Cacti.begin() }; it != m_Cacti.end();)
	{
		if (it->GetAvatar().leftBottom.x < leftBottom.x)
			it = m_Cacti.erase(it);
		else
			++it;
	}
}
