#pragma once

#include "../../Math/MathUtils.h"
#include "../../Texture/Texture.h"

class Dino final
{
public:
	Dino(const MathUtils::Point2f position, const float speed);

	void Update() noexcept;
	void Render() const noexcept;

private:
	MathUtils::Point2f m_Position;
	MathUtils::Vector2f m_Velocity;

	Texture m_Texture;

	float m_Speed;
	bool m_IsJumping;
};
