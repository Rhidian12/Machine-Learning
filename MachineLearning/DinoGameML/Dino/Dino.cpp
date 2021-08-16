#include "Dino.h"
#include "../../Renderer/Renderer.h"
#include "../Ground/Ground.h"
#include "../Cactus/Cactus.h"

#include <SDL.h>

extern bool g_DoContinue;

Dino::Dino(const MathUtils::Point2f position, Ground* const pGround)
	: m_Texture{ "DinoGameML/Textures/Dino.png" }
	, m_Avatar{ position, static_cast<float>(m_Texture.GetWidth()), static_cast<float>(m_Texture.GetHeight()) }
	, m_Velocity{}
	, m_pGround{ pGround }
	, m_JumpSpeed{ 300.f }
	, m_IsJumping{}
	, m_Gravity{ 981.f }
	, m_StartPosition{ position }
	, m_IsDead{}
{
	m_Avatar.leftBottom.y += m_Texture.GetHeight();
}

void Dino::Update(const float dt, const std::vector<Cactus>& cacti) noexcept
{
	if (m_IsJumping) // if we're in the air
		m_Velocity.y -= m_Gravity * dt; // Apply gravity
	else
		m_Velocity.y = 0.f; // just set this to 0.f if we're on the ground

	HandleJump(); // Handle (for now) player input

	m_Avatar.leftBottom += m_Velocity * dt; // Add velocity to position

	HandleCollisions(cacti);
}

void Dino::Render() const noexcept
{
	Renderer::GetInstance()->Render(&m_Texture, m_Avatar.leftBottom);
}

void Dino::Reset() noexcept
{
	m_Avatar.leftBottom = m_StartPosition;
	m_IsJumping = false;
	m_IsDead = false;
	m_Velocity = MathUtils::Vector2f{};
}

const MathUtils::Rectf& Dino::GetAvatar() const noexcept
{
	return m_Avatar;
}

const float Dino::GetJumpSpeed() const noexcept
{
	return m_JumpSpeed;
}

const float Dino::GetGravity() const noexcept
{
	return m_Gravity;
}

const bool Dino::GetIsDead() const noexcept
{
	return m_IsDead;
}

void Dino::HandleJump() noexcept
{
	if (!m_IsJumping && SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE])
	{
		m_IsJumping = true;
		m_Velocity.y += m_JumpSpeed;
	}
}

void Dino::HandleCollisions(const std::vector<Cactus>& cacti) noexcept
{
	const MathUtils::Rectf groundHitbox{ m_pGround->GetHitbox() };
	if (m_Avatar.leftBottom.y <= groundHitbox.leftBottom.y + groundHitbox.height) // are we going through the ground?
	{
		m_IsJumping = false;
		m_Avatar.leftBottom.y = groundHitbox.leftBottom.y + groundHitbox.height; // make sure we can't go through the ground
	}

	for (const Cactus& cactus : cacti)
	{
		if (MathUtils::IsOverlapping(m_Avatar, cactus.GetAvatar()))
		{
			m_IsDead = true;
			break;
		}
	}
}
