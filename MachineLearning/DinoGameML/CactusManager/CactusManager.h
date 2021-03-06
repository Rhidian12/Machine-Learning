#pragma once
#include "../Cactus/Cactus.h"

#include <vector>

class Dino;

class CactusManager final
{
public:
	CactusManager(Dino* const pDino, const float cactusY);

	void Render() const noexcept;
	void Update(const MathUtils::Point2f& leftBottom, const MathUtils::Point2f& cameraRightBottom, const float dt, const float speed) noexcept;

	void Reset() noexcept;

	const std::vector<Cactus>& GetCacti() const noexcept;

private:
	void SpawnCactus(const MathUtils::Point2f& cameraRightBottom, const float speed) noexcept;
	void RemoveCacti(const MathUtils::Point2f& leftBottom) noexcept;

	Dino* m_pDino;
	std::vector<Cactus> m_Cacti;
	float m_CactusY;
	float m_CactusWidth;
};