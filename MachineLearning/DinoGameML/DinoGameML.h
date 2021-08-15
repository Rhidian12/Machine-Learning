#pragma once

#include "Dino/Dino.h"
#include "Ground/Ground.h"
#include "Cactus/Cactus.h"
#include "Camera/Camera.h"

class DinoGameML final
{
public:
	DinoGameML(const uint32_t windowWidth, const uint32_t windowHeight);

	void Update(const float dt) noexcept;
	void Render() const noexcept;

private:
	Ground m_Ground;
	Cactus m_Cactus;
	Dino m_Dino;
	Camera m_Camera;
};
