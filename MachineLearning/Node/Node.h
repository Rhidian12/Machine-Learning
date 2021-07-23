#pragma once

#include "../Math/MathUtils.h"

#include <stdint.h>
#include <vector>

class Transition;
class Texture;
class Node final
{
public:
	Node(MathUtils::Point2f&& position, MathUtils::RGBColour&& colour, const uint32_t index, const float score);
	~Node();

	Node(const Node& other) noexcept;
	Node(Node&& other) noexcept;
	Node& operator=(const Node& other) noexcept;
	Node& operator=(Node&& other) noexcept;

	void Render() const noexcept;

	void AddTransition(Transition* const pTransition) noexcept;

	const MathUtils::Point2f& GetPosition() const noexcept;
	const float GetScore() const noexcept;

private:
	MathUtils::Point2f m_Position;
	MathUtils::RGBColour m_Colour;
	uint32_t m_Index;
	float m_Score;

	Texture* m_pTexture;

	std::vector<Transition*> m_pTransitions;
};