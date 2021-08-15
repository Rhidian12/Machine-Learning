#include "Dino.h"
#include "../../Renderer/Renderer.h"
#include "../Ground/Ground.h"
#include "../Cactus/Cactus.h"

#include <SDL.h>

#include <iostream>

Dino::Dino(const MathUtils::Point2f position, const float speed, const float maxSpeed, Ground* const pGround, Cactus* const pCactus)
	: m_Texture{ "DinoGameML/Textures/Dino.png" }
	, m_Avatar{ position, static_cast<float>(m_Texture.GetWidth()), static_cast<float>(m_Texture.GetHeight()) }
	, m_Velocity{ m_Speed, 0.f }
	, m_pGround{ pGround }
	, m_pCactus{ pCactus }
	, m_Speed{ speed }
	, m_MaxSpeed{ maxSpeed }
	, m_JumpSpeed{ 300.f }
	, m_IsJumping{}
	, m_Gravity{ 981.f }
	, m_IsMaxSpeedReached{}
{
	m_Avatar.leftBottom.y += m_Texture.GetHeight();
}

void Dino::Update(const float dt) noexcept
{
	if (m_IsJumping) // if we're in the air
		m_Velocity.y -= m_Gravity * dt; // Apply gravity
	else
		m_Velocity.y = 0.f; // just set this to 0.f if we're on the ground

	if (m_Speed < m_MaxSpeed)
		m_Speed += m_MaxSpeed / 1000.f; // Increase speed by 0.1% of max speed
	else if (!m_IsMaxSpeedReached) // no point in setting speed to max speed every frame
	{
		m_Speed = m_MaxSpeed; // make sure we don't exceed the max speed
		m_IsMaxSpeedReached = true;
	}

	m_Velocity.x = m_Speed; // Set horizontal velocity to speed

	HandleJump(); // Handle (for now) player input

	m_Avatar.leftBottom += m_Velocity * dt; // Add velocity to position

	HandleCollisions();
}

void Dino::Render() const noexcept
{
	Renderer::GetInstance()->Render(&m_Texture, m_Avatar.leftBottom);
}

void Dino::HandleJump() noexcept
{
	if (!m_IsJumping && SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE])
	{
		m_IsJumping = true;
		m_Velocity.y += m_JumpSpeed;
	}
}

void Dino::HandleCollisions() noexcept
{
	const MathUtils::Rectf groundHitbox{ m_pGround->GetHitbox() };
	if (m_Avatar.leftBottom.y <= groundHitbox.leftBottom.y + groundHitbox.height) // are we going through the ground?
	{
		m_IsJumping = false;
		m_Avatar.leftBottom.y = groundHitbox.leftBottom.y + groundHitbox.height; // make sure we can't go through the ground
	}

	if (MathUtils::IsOverlapping(m_Avatar, m_pCactus->GetAvatar()))
	{
		std::cout << "HIT" << std::endl;
	}
}
