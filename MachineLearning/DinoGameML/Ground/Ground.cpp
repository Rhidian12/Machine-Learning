#include "Ground.h"
#include "../../Renderer/Renderer.h"

Ground::Ground(const MathUtils::Point2f position)
	: m_Texture{ "DinoGameML/Textures/Ground.png" }
	, m_Hitbox{ position, static_cast<float>(m_Texture.GetWidth()), static_cast<float>(m_Texture.GetHeight()) }
{
}

void Ground::Render() const noexcept
{
	Renderer::GetInstance()->Render(&m_Texture, m_Hitbox.leftBottom);
}

const MathUtils::Rectf& Ground::GetHitbox() const noexcept
{
	return m_Hitbox;
}

const Texture& Ground::GetTexture() const noexcept
{
	return m_Texture;
}
