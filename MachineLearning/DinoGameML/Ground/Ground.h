#pragma once

#include "../../Math/MathUtils.h"
#include "../../Texture/Texture.h"

class Ground final
{
public:
	Ground(const MathUtils::Point2f position);

	void Render() const noexcept;

	const MathUtils::Rectf& GetHitbox() const noexcept;
	const Texture& GetTexture() const noexcept;

private:
	Texture m_Texture;
	MathUtils::Rectf m_Hitbox;
};

