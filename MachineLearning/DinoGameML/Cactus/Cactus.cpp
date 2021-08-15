#include "Cactus.h"
#include "../../Renderer/Renderer.h"

Cactus::Cactus(const MathUtils::Point2f position)
	: m_Position{ position }
	, m_Texture{ "DinoGameML/Textures/Cactus.png" }
{
}

void Cactus::Render() const noexcept
{
	Renderer::GetInstance()->Render(&m_Texture, m_Position);
}
