#include "MathUtils.h"
#include "../Utils/Utils.h"

#include <utility> // std::move
#include <limits> // std::numeric_limits

namespace MathUtils
{
#pragma region Point2f
	Point2f::Point2f()
		: x{}
		, y{}
	{}
	Point2f::Point2f(const float _x, const float _y)
		: x{ _x }
		, y{ _y }
	{}
	Point2f::Point2f(const Point2f& other) noexcept
		: x{ other.x }
		, y{ other.y }
	{}
	Point2f::Point2f(Point2f&& other) noexcept
		: x{ other.x }
		, y{ other.y }
	{}
	Point2f& Point2f::operator=(const Point2f& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	Point2f& Point2f::operator=(Point2f&& other) noexcept
	{
		x = std::move(other.x);
		y = std::move(other.y);
		return *this;
	}
	Point2f Point2f::operator+(const Point2f& rhs) const noexcept
	{
		return Point2f{ x + rhs.x, y + rhs.y };
	}
	Point2f& Point2f::operator+=(const Point2f& rhs) noexcept
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Point2f Point2f::operator-(const Point2f& rhs) const noexcept
	{
		return Point2f{ x - rhs.x, y - rhs.y };
	}
	Point2f& Point2f::operator-=(const Point2f& rhs) noexcept
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Point2f Point2f::operator*(const Point2f& rhs) const noexcept
	{
		return Point2f{ x * rhs.x, y * rhs.y };
	}
	Point2f& Point2f::operator*=(const Point2f& rhs) noexcept
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	Point2f Point2f::operator*(const float rhs) const noexcept
	{
		return Point2f{ x * rhs, y * rhs };
	}
	Point2f& Point2f::operator*=(const float rhs) noexcept
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	Point2f Point2f::operator+(const Vector2f& rhs) const noexcept
	{
		return Point2f{x + rhs.x, y + rhs.y};
	}
	Point2f& Point2f::operator+=(const Vector2f& rhs) noexcept
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	const bool Point2f::operator<(const Point2f& rhs) const noexcept
	{
		return ((x < rhs.x) && (y < rhs.y));
	}
	const bool Point2f::operator>(const Point2f& rhs) const noexcept
	{
		return !operator<(rhs);
	}
	const bool Point2f::operator<=(const Point2f& rhs) const noexcept
	{
		return !(rhs > *this);
	}
	const bool Point2f::operator>=(const Point2f& rhs) const noexcept
	{
		return !(rhs < *this);
	}
	const bool Point2f::operator==(const Point2f& rhs) const noexcept
	{
		return AreEqual(x, rhs.x) && AreEqual(y, rhs.y);
	}
	const bool Point2f::operator!=(const Point2f& rhs) const noexcept
	{
		return !(*this == rhs);
	}
#pragma endregion

#pragma region Vector2f
	Vector2f::Vector2f(const float _x, const float _y)
		: x{ _x }
		, y{ _y }
	{
	}
	Vector2f::Vector2f(const Point2f& point)
		: x{ point.x }
		, y{ point.y }
	{
	}
	Vector2f::Vector2f(const Vector2f& other) noexcept
		: x{ other.x }
		, y{ other.y }
	{
	}
	Vector2f::Vector2f(Vector2f&& other) noexcept
		: x{ std::move(other.x) }
		, y{ std::move(other.y) }
	{
	}
	Vector2f& Vector2f::operator=(const Vector2f& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	Vector2f& Vector2f::operator=(Vector2f&& other) noexcept
	{
		x = std::move(other.x);
		y = std::move(other.y);
		return *this;
	}
	Vector2f& Vector2f::operator/=(const Vector2f& other) noexcept
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Vector2f& Vector2f::operator/=(const float other) noexcept
	{
		x /= other;
		y /= other;
		return *this;
	}
	Vector2f Vector2f::operator*(const float other) const noexcept
	{
		return Vector2f{ x * other, y * other };
	}
#pragma endregion

#pragma region RGB
	RGBColour::RGBColour()
		: r{}
		, g{}
		, b{}
		, a{ 1.f }
	{}
	RGBColour::RGBColour(const float r, const float g, const float b)
		: r{ r }
		, g{ g }
		, b{ b }
		, a{ 1.f }
	{}
	RGBColour::RGBColour(const float r, const float g, const float b, const float a)
		: r{ r }
		, g{ g }
		, b{ b }
		, a{ a }
	{}
	RGBColour::RGBColour(const RGBColour& other) noexcept
		: r{ other.r }
		, g{ other.g }
		, b{ other.b }
		, a{ other.a }
	{}
	RGBColour::RGBColour(RGBColour&& other) noexcept
		: r{ std::move(other.r) }
		, g{ std::move(other.g) }
		, b{ std::move(other.b) }
		, a{ std::move(other.a) }
	{}
	RGBColour& RGBColour::operator=(const RGBColour& other) noexcept
	{
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		return *this;
	}
	RGBColour& RGBColour::operator=(RGBColour&& other) noexcept
	{
		r = std::move(other.r);
		g = std::move(other.g);
		b = std::move(other.b);
		a = std::move(other.a);
		return *this;
	}
#pragma endregion
	Point2f&& RotatePointAroundPoint(const Point2f& pointToRotate, const Point2f& originPoint, const float angle) noexcept
	{
		Point2f newPoint{ pointToRotate };

		const float cosine{ cosf(angle) };
		const float sine{ sinf(angle) };

		// translate to origin
		newPoint -= originPoint;

		// rotate points and translate back to original location
		float newX = newPoint.x * cosine - newPoint.y * sine;
		float newY = newPoint.x * sine + newPoint.y * cosine;

		// translate back to original position
		newPoint = Point2f{ newX + originPoint.x, newY + originPoint.y };

		return std::move(newPoint);
	}
	float Dot(const Vector2f& vectorOne, const Vector2f& vectorTwo) noexcept
	{
		return vectorOne.x * vectorTwo.x + vectorOne.y * vectorTwo.y;
	}
	float MagnitudeSquared(const Vector2f& vector) noexcept
	{
		return Dot(vector, vector);
	}
	float Magnitude(const Vector2f& vector) noexcept
	{
		return sqrtf(MagnitudeSquared(vector));
	}
	float Normalize(Vector2f& vector) noexcept
	{
		float magnitude{ Magnitude(vector) };

		Utils::Assert(magnitude != 0.f, "MathUtils::Normalize() > Magnitude was 0!\n");

		vector /= magnitude;
		return magnitude;
	}
	Vector2f GetNormalized(const Vector2f& vector) noexcept
	{
		float magnitude{ Magnitude(vector) };

		Utils::Assert(magnitude != 0.f, "MathUtils::Normalize() > Magnitude was 0!\n");

		Vector2f newVector{ vector };
		newVector /= magnitude;
		return newVector;
	}
	bool IsOverlapping(const Rectf& a, const Rectf& b) noexcept
	{
		if (a.leftBottom.x > b.leftBottom.x + b.width || b.leftBottom.x > a.leftBottom.x + a.width)
			return false;

		if (a.leftBottom.y > b.leftBottom.y + b.height || b.leftBottom.y > a.leftBottom.y + a.height)
			return false;

		return true;
	}
	bool Rectf::operator==(const Rectf& other) const noexcept
	{
		if (leftBottom != other.leftBottom)
			return false;
		if (!AreEqual(width, other.width))
			return false;
		if (!AreEqual(height, other.height))
			return false;

		return true;
	}
	bool Rectf::operator!=(const Rectf& other) const noexcept
	{
		return !(*this == other);
	}
}