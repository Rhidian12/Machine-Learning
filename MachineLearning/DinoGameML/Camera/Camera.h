#pragma once

#include "../../Math/MathUtils.h"

class Camera
{
public:
	Camera(const uint32_t windowWidth, const uint32_t windowHeight, const MathUtils::Rectf& levelBoundaries = MathUtils::Rectf{});
	virtual ~Camera() = default;

	MathUtils::Point2f Transform(const MathUtils::Rectf& target) noexcept;

	void SetLevelBoundaries(const MathUtils::Rectf& levelBoundaries) noexcept;

private:
	MathUtils::Point2f Track(const MathUtils::Rectf& target);
	void Clamp(MathUtils::Point2f& bottomLeftPos) const;

	MathUtils::Rectf m_LevelBoundaries;
	uint32_t m_WindowWidth;
	uint32_t m_WindowHeight;
};