#pragma once

#include "../../Math/MathUtils.h"

#include <vector>

class Camera
{
public:
	Camera(const uint32_t windowWidth, const uint32_t windowHeight, const MathUtils::Rectf& levelBoundaries = MathUtils::Rectf{});
	virtual ~Camera() = default;

	MathUtils::Point2f Transform(const MathUtils::Rectf& target) noexcept;

	void SetLevelBoundaries(const MathUtils::Rectf& levelBoundaries) noexcept;

	void PushStack(MathUtils::Point2f offset) noexcept;
	void PopStack() noexcept;

	const MathUtils::Point2f GetOffset() const noexcept;

private:
	MathUtils::Point2f Track(const MathUtils::Rectf& target) noexcept;
	void Clamp(MathUtils::Point2f& bottomLeftPos);

	MathUtils::Rectf m_LevelBoundaries;
	uint32_t m_WindowWidth;
	uint32_t m_WindowHeight;

	std::vector<MathUtils::Rectf> m_Stack;
};