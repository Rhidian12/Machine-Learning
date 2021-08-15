#pragma once

#include "Dino/Dino.h"
#include "Ground/Ground.h"
#include "Cactus/Cactus.h"

class DinoGameML final
{
public:
	DinoGameML();

	void Update(const float dt) noexcept;
	void Render() const noexcept;

private:
	Ground m_Ground;
	Cactus m_Cactus;
	Dino m_Dino;
};
