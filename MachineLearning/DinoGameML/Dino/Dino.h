#pragma once

#include "../../Math/MathUtils.h"
#include "../../Texture/Texture.h"

class Ground;
class Cactus;
class Dino final
{
public:
	Dino(const MathUtils::Point2f position, const float speed, const float maxSpeed, Ground* const pGround, Cactus* const pCactus);

	void Update(const float dt) noexcept;
	void Render() const noexcept;

private:
	void HandleJump() noexcept;
	void HandleCollisions() noexcept;

	Texture m_Texture;

	MathUtils::Rectf m_Avatar;
	MathUtils::Vector2f m_Velocity;

	Ground* m_pGround;
	Cactus* m_pCactus;

	float m_Speed;
	float m_MaxSpeed;
	float m_JumpSpeed;
	bool m_IsJumping;
	float m_Gravity;
	bool m_IsMaxSpeedReached;
};
