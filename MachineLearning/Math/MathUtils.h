#pragma once

#include <type_traits>
#include <utility>

namespace MathUtils
{
	constexpr float PI = 3.14159265358979323846f;

	struct Vector2f;
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
		Point2f operator+(const Point2f& rhs) const noexcept;
		Point2f& operator+=(const Point2f& rhs) noexcept;
		Point2f operator-(const Point2f& rhs) const noexcept;
		Point2f& operator-=(const Point2f& rhs) noexcept;
		Point2f operator*(const Point2f& rhs) const noexcept;
		Point2f& operator*=(const Point2f& rhs) noexcept;
		Point2f operator*(const float rhs) const noexcept;
		Point2f& operator*=(const float rhs) noexcept;
		Point2f operator+(const Vector2f& rhs) const noexcept;
		Point2f& operator+=(const Vector2f& rhs) noexcept;
		const bool operator<(const Point2f& rhs) const noexcept;
		const bool operator>(const Point2f& rhs) const noexcept;
		const bool operator<=(const Point2f& rhs) const noexcept;
		const bool operator>=(const Point2f& rhs) const noexcept;
		const bool operator==(const Point2f& rhs) const noexcept;
		const bool operator!=(const Point2f& rhs) const noexcept;
#pragma endregion
	};

	Point2f&& RotatePointAroundPoint(const Point2f& pointToRotate, const Point2f& originPoint, const float angle) noexcept;

	struct Vector2f final
	{
		explicit Vector2f(const float _x = 0.f, const float _y = 0.f);
		explicit Vector2f(const Point2f& point);

		float x, y;

#pragma region RuleOf5
		Vector2f(const Vector2f& other) noexcept;
		Vector2f(Vector2f&& other) noexcept;
		Vector2f& operator=(const Vector2f& other) noexcept;
		Vector2f& operator=(Vector2f&& other) noexcept;
#pragma endregion

#pragma region Operators
		Vector2f& operator/=(const Vector2f& other) noexcept;
		Vector2f& operator/=(const float other) noexcept;
		Vector2f operator*(const float other) const noexcept;
#pragma endregion
	};

	struct Rectf final
	{
		Rectf()
			: leftBottom{}
			, width{}
			, height{}
		{}
		Rectf(Point2f _leftBottom, float _width, float _height)
			: leftBottom{ _leftBottom }
			, width{ _width }
			, height{ _height }
		{}

		Point2f leftBottom;
		float width, height;

#pragma region operators
		bool operator==(const Rectf& other) const noexcept;
		bool operator!=(const Rectf& other) const noexcept;
#pragma endregion
	};

	float Dot(const Vector2f& vectorOne, const Vector2f& vectorTwo) noexcept;
	float MagnitudeSquared(const Vector2f& vector) noexcept;
	float Magnitude(const Vector2f& vector) noexcept;
	float Normalize(Vector2f& vector) noexcept;
	Vector2f GetNormalized(const Vector2f& vector) noexcept;

	bool IsOverlapping(const Rectf& a, const Rectf& b) noexcept;

	struct RGBColour final
	{
		RGBColour();
		RGBColour(const float r, const float g, const float b);
		RGBColour(const float r, const float g, const float b, const float a);

#pragma region RuleOf5
		RGBColour(const RGBColour& other) noexcept;
		RGBColour(RGBColour&& other) noexcept;
		RGBColour& operator=(const RGBColour& other) noexcept;
		RGBColour& operator=(RGBColour&& other) noexcept;
#pragma endregion

		float r, g, b, a;
	};

	struct ConvertToBottomLeftOrigin
	{
		inline static int windowHeight{};

		Point2f operator()(const Point2f& position) const noexcept
		{
			return Point2f{ position.x, windowHeight - position.y };
		}
	};

	template<typename FloatingPoint, typename = std::enable_if_t<std::is_floating_point_v<FloatingPoint>>>
	constexpr FloatingPoint ToRadians(const FloatingPoint& value) noexcept
	{
		return value * PI / FloatingPoint(180.f);
	}

	template<typename FloatingPoint, typename = std::enable_if_t<std::is_floating_point_v<FloatingPoint>>>
	constexpr FloatingPoint ToDegrees(const FloatingPoint& value) noexcept
	{
		return value * FloatingPoint(180.f) / PI;
	}

	template<typename FundamentalType, typename = std::enable_if_t<std::is_fundamental_v<FundamentalType>>>
	constexpr bool AreEqual(const FundamentalType a, const FundamentalType b)
	{
		return abs(a - b) <= std::numeric_limits<FundamentalType>::epsilon();
	}

	template<typename Type>
	constexpr void Clamp(Type& value, const Type& min, const Type& max) noexcept
	{
		if (value < min)
			value = min;

		if (value > max)
			value = max;
	}
}