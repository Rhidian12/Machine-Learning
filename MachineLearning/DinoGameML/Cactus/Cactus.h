#pragma once

#include "../../Math/MathUtils.h"
#include "../../Texture/Texture.h"

class Cactus final
{
public:
	Cactus(const MathUtils::Point2f position);

	void Render() const noexcept;

private:
	Texture m_Texture;
	MathUtils::Point2f m_Position;
};