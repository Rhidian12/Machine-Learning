#include "DinoGameML.h"
#include "../Math/MathUtils.h"
#include "../Renderer/Renderer.h"

DinoGameML::DinoGameML(const uint32_t windowWidth, const uint32_t windowHeight)
	: m_Ground{ MathUtils::Point2f{0.f, 24.f} }
	, m_Dino{ MathUtils::Point2f{50.f, 15.f}, 20.f, 200.f, &m_Ground }
	, m_Camera{ windowWidth, windowHeight, MathUtils::Rectf{MathUtils::Point2f{0.f, 0.f}, m_Ground.GetHitbox().width, static_cast<float>(windowHeight) } }
	, m_CactusManager{ &m_Dino, 15.f }
	, m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
	, m_CameraLeftBottom{}
{
	Renderer::GetInstance()->SetCamera(&m_Camera);
}

void DinoGameML::Update(const float dt) noexcept
{
	m_Dino.Update(dt, m_CactusManager.GetCacti());
	m_CactusManager.Update(m_CameraLeftBottom, MathUtils::Point2f{ m_CameraLeftBottom.x + m_WindowWidth, m_CameraLeftBottom.y });
}

void DinoGameML::Render() noexcept
{
	m_CameraLeftBottom = m_Camera.Transform(m_Dino.GetAvatar());
	{
		m_Dino.Render();
		m_Ground.Render();
		m_CactusManager.Render();
	}
	m_Camera.PopStack();
}
