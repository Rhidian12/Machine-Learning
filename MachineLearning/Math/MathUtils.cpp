#include "MathUtils.h"

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
	Point2f&& Point2f::operator+(const Point2f& rhs) const noexcept
	{
		return std::move(Point2f{ x + rhs.x, y + rhs.y });
	}
	Point2f& Point2f::operator+=(const Point2f& rhs) noexcept
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Point2f&& Point2f::operator-(const Point2f& rhs) const noexcept
	{
		return std::move(Point2f{ x - rhs.x, y - rhs.y });
	}
	Point2f& Point2f::operator-=(const Point2f& rhs) noexcept
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Point2f&& Point2f::operator*(const Point2f& rhs) const noexcept
	{
		return std::move(Point2f{ x * rhs.x, y * rhs.y });
	}
	Point2f& Point2f::operator*=(const Point2f& rhs) noexcept
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	Point2f&& Point2f::operator*(const float rhs) const noexcept
	{
		return std::move(Point2f{ x * rhs, y * rhs });
	}
	Point2f& Point2f::operator*=(const float rhs) noexcept
	{
		x *= rhs;
		y *= rhs;
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
		return (((x - rhs.x) <= std::numeric_limits<float>::epsilon()) && ((y - rhs.y) <= std::numeric_limits<float>::epsilon()));
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
}
#pragma endregion