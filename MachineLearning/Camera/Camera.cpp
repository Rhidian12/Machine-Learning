#include "Camera.h"
#include "../../Renderer/Renderer.h"
#include "../../Utils/Utils.h"

#include <SDL.h> // SDL_RenderSetViewport()

Camera::Camera(const uint32_t windowWidth, const uint32_t windowHeight, const MathUtils::Rectf& levelBoundaries)
	: m_LevelBoundaries{ levelBoundaries }
	, m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
{
}

MathUtils::Point2f Camera::Transform(const MathUtils::Rectf& target) noexcept
{
	// == Track Target And Make Sure Camera Does Not Leave LevelBoundaries ==
	MathUtils::Point2f camPosition{ Track(target) };
	Clamp(camPosition);

	// == Translate The World ==
	PushStack(MathUtils::Point2f{ -camPosition.x, -camPosition.y });

	// == Draw Camera View For Debugging Purposes ==
	Utils::DrawRectangle(MathUtils::Rectf{ camPosition, 100.f, 100.f }, MathUtils::RGBColour{ 255.f, 0.f, 0.f });

	return camPosition;
}

void Camera::SetLevelBoundaries(const MathUtils::Rectf& levelBoundaries) noexcept
{
	m_LevelBoundaries = levelBoundaries;
}

MathUtils::Point2f Camera::Track(const MathUtils::Rectf& target) noexcept
{
	// == Get The Center Coordinates Of The Target ==
	float x = target.leftBottom.x + (target.width / 2);
	float y = target.leftBottom.y + (target.height / 2);

	// == Return The Center Of The Target - Center Of The Screen ==
	return MathUtils::Point2f{ x - static_cast<float>(m_WindowWidth) / 2.f,y - static_cast<float>(m_WindowHeight) / 2.f };
}

void Camera::Clamp(MathUtils::Point2f& bottomLeftPos)
{
	// == Check If The LevelBoundaries Are Initialised ==
	Utils::Assert(m_LevelBoundaries != MathUtils::Rectf{}, "Camera Levelboundaries were not set!");

	// == Check Level Boundaries ==
	if (bottomLeftPos.x <= m_LevelBoundaries.leftBottom.x)
		bottomLeftPos.x = m_LevelBoundaries.leftBottom.x;

	if (bottomLeftPos.x + m_WindowWidth >= m_LevelBoundaries.leftBottom.x + m_LevelBoundaries.width)
		bottomLeftPos.x = m_LevelBoundaries.leftBottom.x + m_LevelBoundaries.width - m_WindowWidth;

	if (bottomLeftPos.y <= m_LevelBoundaries.leftBottom.y)
		bottomLeftPos.y = m_LevelBoundaries.leftBottom.y;

	if (bottomLeftPos.y + m_WindowHeight >= m_LevelBoundaries.leftBottom.y + m_LevelBoundaries.height)
		bottomLeftPos.y = m_LevelBoundaries.leftBottom.y + m_LevelBoundaries.height - m_WindowHeight;
}

void Camera::PushStack(MathUtils::Point2f offset) noexcept
{
	if (m_Stack.empty())
		m_Stack.push_back(MathUtils::Rectf{ offset, static_cast<float>(m_WindowWidth), static_cast<float>(m_WindowHeight) });
	else
	{
		MathUtils::Point2f totalOffset{ offset.x + m_Stack.back().leftBottom.x, offset.y + m_Stack.back().leftBottom.y };
		m_Stack.push_back(MathUtils::Rectf{ totalOffset, static_cast<float>(m_WindowWidth), static_cast<float>(m_WindowHeight) });
	}
}

void Camera::PopStack() noexcept
{
	m_Stack.pop_back();
}

const MathUtils::Point2f Camera::GetOffset() const noexcept
{
	if (m_Stack.empty())
		return MathUtils::Point2f{};
	else
		return m_Stack.back().leftBottom;
}
