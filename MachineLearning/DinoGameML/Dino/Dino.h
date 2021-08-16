#pragma once

#include "../../Math/MathUtils.h"
#include "../../Texture/Texture.h"

#include <vector>

class Ground;
class Cactus;
class Dino final
{
public:
	Dino(const MathUtils::Point2f position, Ground* const pGround);

	void Update(const float dt, const std::vector<Cactus>& cacti) noexcept;
	void Render() const noexcept;

	const MathUtils::Rectf& GetAvatar() const noexcept;
	const float GetJumpSpeed() const noexcept;
	const float GetGravity() const noexcept;

private:
	void HandleJump() noexcept;
	void HandleCollisions(const std::vector<Cactus>& cacti) noexcept;

	Texture m_Texture;

	MathUtils::Rectf m_Avatar;
	MathUtils::Vector2f m_Velocity;

	Ground* m_pGround;

	float m_JumpSpeed;
	bool m_IsJumping;
	float m_Gravity;
	bool m_IsMaxSpeedReached;
};
