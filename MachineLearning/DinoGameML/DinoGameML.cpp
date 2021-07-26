#include "DinoGameML.h"
#include "../Math/MathUtils.h"

DinoGameML::DinoGameML()
	: m_Ground{ MathUtils::Point2f{0.f, 24.f} }
	, m_Dino{ MathUtils::Point2f{50.f, 24.f}, 10.f, 10.f, &m_Ground }
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
}
