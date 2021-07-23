#include "Transition.h"
#include "../Node/Node.h"
#include "../Utils/Utils.h"

#include <utility> // std::move

Transition::Transition(Node* const pFromNode, Node* const pToNode)
	: m_pFromNode{ pFromNode }
	, m_pToNode{ pToNode }
	, m_Colour{ 100.f, 100.f, 100.f }
	, m_IsRendered{}
{
	m_pFromNode->AddTransition(this);
	m_pToNode->AddTransition(this);
}

#pragma region RuleOf5

Transition::Transition(const Transition& other) noexcept
	: m_pFromNode{ other.m_pFromNode }
	, m_pToNode{ other.m_pToNode }
	, m_IsRendered{ other.m_IsRendered }
{
}

Transition::Transition(Transition&& other) noexcept
	: m_pFromNode{ std::move(other.m_pFromNode) }
	, m_pToNode{ std::move(other.m_pToNode) }
	, m_IsRendered{ std::move(other.m_IsRendered) }
{
}

Transition& Transition::operator=(const Transition& other) noexcept
{
	m_pFromNode = other.m_pFromNode;
	m_pToNode = other.m_pToNode;
	m_IsRendered = other.m_IsRendered;
	return *this;
}

Transition& Transition::operator=(Transition&& other) noexcept
{
	m_pFromNode = std::move(other.m_pFromNode);
	m_pToNode = std::move(other.m_pToNode);
	m_IsRendered = std::move(other.m_IsRendered);
	return *this;
}

#pragma endregion

void Transition::Render(const int radius) const noexcept
{
	using namespace MathUtils;
	if (!m_IsRendered)
	{
		Point2f from{ m_pFromNode->GetPosition().x, m_pFromNode->GetPosition().y };
		Point2f to{ m_pToNode->GetPosition().x, m_pToNode->GetPosition().y };

		Vector2f dir{ to.x - from.x, to.y - from.y };
		Normalize(dir);

		Vector2f perpendicularDir{ dir.y, -dir.x };
		const float offset{ static_cast<float>(radius) };
		from = Point2f{ from.x + perpendicularDir.x * offset, from.y + perpendicularDir.y * offset };
		to = Point2f{ to.x + perpendicularDir.x * offset, to.y + perpendicularDir.y * offset };

		Utils::DrawLine(from, to, m_Colour);
		DrawTriangle(from, to);
	}
}

void Transition::SetIsRendered(const bool isRendered) noexcept
{
	m_IsRendered = isRendered;
}

const bool Transition::GetIsRendered() const noexcept
{
	return m_IsRendered;
}

Node* const Transition::GetFromNode() const noexcept
{
	return m_pFromNode;
}

Node* const Transition::GetToNode() const noexcept
{
	return m_pToNode;
}

void Transition::DrawTriangle(const MathUtils::Point2f& begin, const MathUtils::Point2f& end) const noexcept
{
	using namespace MathUtils;

	const Point2f center{ (begin.x + end.x) / 2.f, (begin.y + end.y) / 2.f };

	const float triangleSize{ 10.f };

	const float angleBetweenTwoPoints{ atan2f(end.y - begin.y, end.x - begin.x) - ToRadians(90.f) }; // idk why i need to do - 90, but fuck it

	Point2f upPoint{};
	Point2f leftPoint{ center.x - triangleSize, center.y };
	Point2f rightPoint{ center.x + triangleSize, center.y };

	if (begin.y < end.y) // we're going up
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
