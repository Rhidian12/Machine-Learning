#pragma once

#include "../../Math/MathUtils.h"
#include "../../Texture/Texture.h"

class Ground;
class Dino final
{
public:
	Dino(const MathUtils::Point2f position, const float speed, const float maxSpeed, Ground* const pGround);

	void Update(const float dt) noexcept;
	void Render() const noexcept;

private:
	void HandleJump() noexcept;

	MathUtils::Point2f m_Position;
	MathUtils::Vector2f m_Velocity;

	Texture m_Texture;

	Ground* m_pGround;

	float m_Speed;
	float m_MaxSpeed;
	float m_JumpSpeed;
	bool m_IsJumping;
};
