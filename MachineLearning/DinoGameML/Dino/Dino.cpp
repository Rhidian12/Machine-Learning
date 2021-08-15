#include "Dino.h"
#include "../../Renderer/Renderer.h"
#include "../Ground/Ground.h"

#include <SDL.h>

Dino::Dino(const MathUtils::Point2f position, const float speed, const float maxSpeed, Ground* const pGround)
	: m_Position{ position }
	, m_Velocity{ m_Speed, 0.f }
	, m_Texture{ "DinoGameML/Textures/Dino.png" }
	, m_pGround{ pGround }
	, m_Speed{ speed }
	, m_MaxSpeed{ maxSpeed }
	, m_JumpSpeed{ 300.f }
	, m_IsJumping{}
	, m_Gravity{ 981.f }
{
	m_Position.y += m_Texture.GetHeight();
}

void Dino::Update(const float dt) noexcept
{
	if (m_IsJumping) // if we're in the air
		m_Velocity.y -= m_Gravity * dt; // Apply gravity
	else
		m_Velocity.y = 0.f; // just set this to 0.f if we're on the ground

	if (m_Speed < m_MaxSpeed)
		m_Speed += m_MaxSpeed / 100.f; // Increase speed by 1% of max speed
	else
		m_Speed = m_MaxSpeed; // make sure we don't exceed the max speed

	m_Velocity.x = m_Speed; // Set horizontal velocity to speed

	HandleJump(); // Handle (for now) player input

	m_Position += m_Velocity * dt; // Add velocity to position

	if (m_Position.y <= m_pGround->GetPosition().y + m_pGround->GetTexture().GetHeight()) // are we going through the ground?
	{
		m_IsJumping = false;
		m_Position.y = m_pGround->GetPosition().y + m_pGround->GetTexture().GetHeight(); // make sure we can't go through the ground
	}
}

void Dino::Render() const noexcept
{
	Renderer::GetInstance()->Render(&m_Texture, m_Position);
}

void Dino::HandleJump() noexcept
{
	if (!m_IsJumping && SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE])
	{
		m_IsJumping = true;
		m_Velocity.y += m_JumpSpeed;
	}
}
