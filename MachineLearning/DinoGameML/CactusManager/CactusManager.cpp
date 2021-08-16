#include "CactusManager.h"
#include "../Dino/Dino.h"

CactusManager::CactusManager(Dino* const pDino, const float cactusY)
	: m_pDino{ pDino }
	, m_Cacti{}
	, m_CactusY{ cactusY }
	, m_CactusWidth{ 24.f }
{
}

void CactusManager::Render() const noexcept
{
	for (const Cactus& cactus : m_Cacti)
		cactus.Render();
}

void CactusManager::Update(const MathUtils::Point2f& cameraLeftBottom, const MathUtils::Point2f& cameraRightBottom, const float dt, const float speed) noexcept
{
	if (m_Cacti.size() < 5)
		SpawnCactus(cameraRightBottom, speed);

	RemoveCacti(cameraLeftBottom);

	for (Cactus& cactus : m_Cacti)
		cactus.Update(dt, speed);
}

const std::vector<Cactus>& CactusManager::GetCacti() const noexcept
{
	return m_Cacti;
}

void CactusManager::SpawnCactus(const MathUtils::Point2f& cameraRightBottom, const float speed) noexcept
{
	// the minimum distance between cacti needs to be [Dino Current Speed] + [Time from Jump => Ground] + Offset?
	// the maximum distance can be this distance * [number]

	// (m / s) / (m / s^2) <==> (m/s) * (s^2 / m) <==> (s^2*m) / (s * m) = s
	if (m_Cacti.empty())
	{
		if (MathUtils::RandomNumber(0, 2) % 2 == 0)
			m_Cacti.push_back(Cactus{ MathUtils::Point2f{cameraRightBottom.x, m_CactusY}, true });
		else
			m_Cacti.push_back(Cactus{ MathUtils::Point2f{cameraRightBottom.x, m_CactusY}, false });
	}
	else
	{
		const float totalTime{ m_pDino->GetJumpSpeed() / m_pDino->GetGravity() * 2.f }; // velocity / gravity * 2.f == total time a jump takes

		const float minDistance{ abs(speed) * totalTime + m_CactusWidth };
		const float maxDistance{ minDistance * 1.5f };

		const float minDistanceSquared{ MathUtils::Square(minDistance) };

		MathUtils::Point2f coordsOfLastCactus{ m_Cacti.back().GetAvatar().leftBottom };
		MathUtils::Point2f coord{ 0.f, m_CactusY };

		do
		{
			coord.x = MathUtils::RandomNumber(cameraRightBottom.x, cameraRightBottom.x + coordsOfLastCactus.x + maxDistance);
		} while (MathUtils::MagnitudeSquared(MathUtils::Vector2f{ coordsOfLastCactus - coord }) <= minDistanceSquared);

		if (MathUtils::RandomNumber(0, 2) % 2 == 0)
			m_Cacti.push_back(Cactus{ coord, true });
		else
			m_Cacti.push_back(Cactus{ coord, false });
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
