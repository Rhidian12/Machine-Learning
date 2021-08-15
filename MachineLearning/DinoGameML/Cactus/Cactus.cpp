#include "Cactus.h"
#include "../../Renderer/Renderer.h"

Cactus::Cactus(const MathUtils::Point2f position, const bool isDouble)
	: m_Texture{ "DinoGameML/Textures/Cactus.png" }
	, m_IsDouble{ isDouble }
	, m_Avatar{ position, m_Texture.GetWidth(), m_Texture.GetHeight() }
{
}

void Cactus::Render() const noexcept
{
	Renderer::GetInstance()->Render(&m_Texture, m_Avatar.leftBottom);

	if (m_IsDouble)
		Renderer::GetInstance()->Render(&m_Texture, MathUtils::Point2f{ m_Avatar.leftBottom.x + m_Texture.GetWidth(), m_Avatar.leftBottom.y });
}
