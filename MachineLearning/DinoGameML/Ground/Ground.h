#pragma once

#include "../../Math/MathUtils.h"
#include "../../Texture/Texture.h"

class Ground final
{
public:
	Ground(const MathUtils::Point2f position);

	void Render() const noexcept;

	const MathUtils::Point2f& GetPosition() const noexcept;

private:
	MathUtils::Point2f m_Position;
	Texture m_Texture;
};

