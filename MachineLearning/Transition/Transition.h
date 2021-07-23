#pragma once
#include <stdint.h>

#include "../Math/MathUtils.h"

class Node;
class Transition final
{
public:
	Transition(Node* const pFromNode, Node* const pToNode);

	Transition(const Transition& other) noexcept;
	Transition(Transition&& other) noexcept;
	Transition& operator=(const Transition& other) noexcept;
	Transition& operator=(Transition&& other) noexcept;

	void Render(const int radius) const noexcept;

	void SetIsRendered(const bool isRendered) noexcept;
	const bool GetIsRendered() const noexcept;

	Node* const GetFromNode() const noexcept;
	Node* const GetToNode() const noexcept;

private:
	Node* m_pFromNode;
	Node* m_pToNode;

	bool m_IsRendered;

	MathUtils::RGBColour m_Colour;

	void DrawTriangle(const MathUtils::Point2f& begin, const MathUtils::Point2f& end) const noexcept;
};