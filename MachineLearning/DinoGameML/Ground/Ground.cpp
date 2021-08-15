#include "Ground.h"
#include "../../Renderer/Renderer.h"

Ground::Ground(const MathUtils::Point2f position)
	: m_Position{ position }
	, m_Texture{ "DinoGameML/Textures/Ground.png" }
{
}

void Ground::Render() const noexcept
{
	Renderer::GetInstance()->Render(&m_Texture, m_Position);
}

const MathUtils::Point2f& Ground::GetPosition() const noexcept
{
	return m_Position;
}

const Texture& Ground::GetTexture() const noexcept
{
	return m_Texture;
}
