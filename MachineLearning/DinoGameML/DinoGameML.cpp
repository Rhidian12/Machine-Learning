#include "DinoGameML.h"
#include "../Math/MathUtils.h"

DinoGameML::DinoGameML()
	: m_Ground{ MathUtils::Point2f{0.f, 24.f} }
	, m_Cactus{ MathUtils::Point2f{300.f, 15.f}, false }
	, m_Dino{ MathUtils::Point2f{50.f, 15.f}, 20.f, 200.f, &m_Ground, &m_Cactus }
{
}

void DinoGameML::Update(const float dt) noexcept
{
	m_Dino.Update(dt);
}

void DinoGameML::Render() const noexcept
{
	m_Dino.Render();
	m_Ground.Render();
	m_Cactus.Render();
}
