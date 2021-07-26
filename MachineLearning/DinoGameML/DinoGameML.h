#pragma once

#include "Dino/Dino.h"
#include "Ground/Ground.h"

class DinoGameML final
{
public:
	DinoGameML();

	void Update(const float dt) noexcept;
	void Render() const noexcept;

private:
	Ground m_Ground;
	Dino m_Dino;
};
