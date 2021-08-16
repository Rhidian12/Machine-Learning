#pragma once

#include "Dino/Dino.h"
#include "Ground/Ground.h"
#include "Cactus/Cactus.h"
#include "../Camera/Camera.h"
#include "CactusManager/CactusManager.h"

class DinoGameML final
{
public:
	DinoGameML(const uint32_t windowWidth, const uint32_t windowHeight);

	void Update(const float dt) noexcept;
	void Render() noexcept;

private:
	Ground m_Ground;
	Dino m_Dino;
	Camera m_Camera;
	CactusManager m_CactusManager;

	uint32_t m_WindowWidth;
	uint32_t m_WindowHeight;

	MathUtils::Point2f m_CameraLeftBottom;

	float m_Speed;
	float m_MaxSpeed;
};
