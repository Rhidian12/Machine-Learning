#pragma once

#include "../../Math/MathUtils.h"
#include "../../Texture/Texture.h"

class Ground final
{
public:
	Ground(const MathUtils::Point2f position);

private:
	MathUtils::Point2f m_Position;
	Texture m_Texture;
};

