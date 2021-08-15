#include "DinoGameML.h"
#include "../Math/MathUtils.h"
#include "../Renderer/Renderer.h"

DinoGameML::DinoGameML(const uint32_t windowWidth, const uint32_t windowHeight)
	: m_Ground{ MathUtils::Point2f{0.f, 24.f} }
	, m_Cactus{ MathUtils::Point2f{300.f, 15.f}, false }
	, m_Dino{ MathUtils::Point2f{50.f, 15.f}, 20.f, 200.f, &m_Ground, &m_Cactus }
	, m_Camera{ windowWidth, windowHeight, MathUtils::Rectf{MathUtils::Point2f{0.f, 0.f}, m_Ground.GetHitbox().width, static_cast<float>(windowHeight) } }
{
	Renderer::GetInstance()->SetCamera(&m_Camera);
}

void DinoGameML::Update(const float dt) noexcept
{
	m_Dino.Update(dt);
}

void DinoGameML::Render() noexcept
{
	m_Camera.Transform(m_Dino.GetAvatar());
	m_Dino.Render();
	m_Ground.Render();
	m_Cactus.Render();
	m_Camera.PopStack();
}
