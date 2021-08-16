#pragma once

#include "../../Math/MathUtils.h"
#include "../../Texture/Texture.h"

class Cactus final
{
public:
	Cactus(const MathUtils::Point2f position, const bool isDouble);

	void Render() const noexcept;
	void Update(const float dt, const float speed) noexcept;

	const MathUtils::Rectf& GetAvatar() const noexcept;

private:
	Texture m_Texture;
	bool m_IsDouble;
	MathUtils::Rectf m_Avatar;
};