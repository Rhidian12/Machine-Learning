#include "Transition.h"
#include "../Node/Node.h"
#include "../Utils/Utils.h"

#include <utility> // std::move

Transition::Transition(Node* const pFromNode, Node* const pToNode)
	: m_pFromNode{ pFromNode }
	, m_pToNode{ pToNode }
	, m_Colour{ 100.f, 100.f, 100.f }
{
}

Transition::Transition(const Transition& other) noexcept
	: m_pFromNode{ other.m_pFromNode }
	, m_pToNode{ other.m_pToNode }
{
}

Transition::Transition(Transition&& other) noexcept
	: m_pFromNode{ std::move(other.m_pFromNode) }
	, m_pToNode{ std::move(other.m_pToNode) }
{
}

Transition& Transition::operator=(const Transition& other) noexcept
{
	m_pFromNode = other.m_pFromNode;
	m_pToNode = other.m_pToNode;
	return *this;
}

Transition& Transition::operator=(Transition&& other) noexcept
{
	m_pFromNode = std::move(other.m_pFromNode);
	m_pToNode = std::move(other.m_pToNode);
	return *this;
}

void Transition::Render() const noexcept
{
	Utils::DrawLine(m_pFromNode->GetPosition(), m_pToNode->GetPosition(), m_Colour);
	DrawTriangle();
}

Node* const Transition::GetFromNode() const noexcept
{
	return m_pFromNode;
}

Node* const Transition::GetToNode() const noexcept
{
	return m_pToNode;
}

void Transition::DrawTriangle() const noexcept
{
	using namespace MathUtils;

	const Point2f& fromPoint{ m_pFromNode->GetPosition() };
	const Point2f& toPoint{ m_pToNode->GetPosition() };
	const Point2f center{ (fromPoint.x + toPoint.x) / 2.f, (fromPoint.y + toPoint.y) / 2.f };

	const float triangleSize{ 10.f };

	const float angleBetweenTwoPoints{ atan2f(toPoint.y - fromPoint.y, toPoint.x - fromPoint.x) - ToRadians(90.f) }; // idk why i need to do - 90, but fuck it

	Point2f upPoint{};
	Point2f leftPoint{ center.x - triangleSize, center.y };
	Point2f rightPoint{ center.x + triangleSize, center.y };

	if (fromPoint.y < toPoint.y) // we're going up
		upPoint = Point2f{ center.x, center.y + triangleSize };
	else // we're going down
		upPoint = Point2f{ center.x, center.y + triangleSize };

	upPoint = RotatePointAroundPoint(upPoint, center, angleBetweenTwoPoints);
	leftPoint = RotatePointAroundPoint(leftPoint, center, angleBetweenTwoPoints);
	rightPoint = RotatePointAroundPoint(rightPoint, center, angleBetweenTwoPoints);

	Utils::DrawLine(rightPoint, leftPoint, m_Colour);
	Utils::DrawLine(leftPoint, upPoint, m_Colour);
	Utils::DrawLine(upPoint, rightPoint, m_Colour);
}
