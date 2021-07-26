#include "Dino.h"
#include "../../Renderer/Renderer.h"

Dino::Dino(const MathUtils::Point2f position, const float speed)
	: m_Position{ position }
	, m_Velocity{ m_Speed, 0.f }
	, m_Texture{ "../Textures/Dino.png" }
	, m_Speed{ speed }
	, m_IsJumping{}
{
}

void Dino::Update() noexcept
{
	m_Velocity.y -= 9.81f; // Apply gravity
}

void Dino::Render() const noexcept
{
	Renderer::GetInstance()->Render(&m_Texture, m_Position);
}
