#pragma once
#include <string> // std::string

#include "../Math/MathUtils.h"

namespace Utils
{
#ifdef _DEBUG
	void Assert(const bool expression, std::string&& message);
#else
	void Assert(const bool expression, std::string&& message);
#endif

	void DrawCircle(const MathUtils::Point2f& position, const int radius, const MathUtils::RGBColour& colour) noexcept;

	template<typename Type>
	inline void SafeDelete(Type*& pData)
	{
		if (pData)
		{
			delete pData;
			pData = nullptr;
		}
	}
}