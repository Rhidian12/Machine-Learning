#pragma once

namespace MathUtils
{
	struct Point2f final
	{
		explicit Point2f();
		explicit Point2f(const float _x, const float _y);

		float x, y;

#pragma region RuleOf5
		Point2f(const Point2f& other) noexcept;
		Point2f(Point2f&& other) noexcept;
		Point2f& operator=(const Point2f& other) noexcept;
		Point2f& operator=(Point2f&& other) noexcept;
#pragma endregion

#pragma region Operators
		Point2f&& operator+(const Point2f& rhs) const noexcept;
		Point2f& operator+=(const Point2f& rhs) noexcept;
		Point2f&& operator-(const Point2f& rhs) const noexcept;
		Point2f& operator-=(const Point2f& rhs) noexcept;
		Point2f&& operator*(const Point2f& rhs) const noexcept;
		Point2f& operator*=(const Point2f& rhs) noexcept;
		Point2f&& operator*(const float rhs) const noexcept;
		Point2f& operator*=(const float rhs) noexcept;
		const bool operator<(const Point2f& rhs) const noexcept;
		const bool operator>(const Point2f& rhs) const noexcept;
		const bool operator<=(const Point2f& rhs) const noexcept;
		const bool operator>=(const Point2f& rhs) const noexcept;
		const bool operator==(const Point2f& rhs) const noexcept;
		const bool operator!=(const Point2f& rhs) const noexcept;
#pragma endregion
	};

	struct Vector2f final
	{
		Vector2f(const float _x = 0.f, const float _y = 0.f);

		float x, y;

#pragma region RuleOf5
		Vector2f(const Vector2f& other) noexcept;
		Vector2f(Vector2f&& other) noexcept;
		Vector2f& operator=(const Vector2f& other) noexcept;
		Vector2f& operator=(Vector2f&& other) noexcept;
#pragma endregion
	};
}