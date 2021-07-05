#pragma once
#include <stdint.h> // uint32_t
#include <vector> // std::vector

class FMatrix final
{
public:
	FMatrix(const uint32_t rows, const uint32_t cols, const float initValue = 0.f);

	FMatrix(const FMatrix& other) noexcept;
	FMatrix(FMatrix&& other) noexcept;
	FMatrix& operator=(const FMatrix& other) noexcept;
	FMatrix& operator=(FMatrix&& other) noexcept;

	void Set(const uint32_t row, const uint32_t col, const float value) noexcept;
	const float Get(const uint32_t row, const uint32_t col) const noexcept;

	void SetAll(const float value) noexcept;

	const uint32_t&& GetNumberOfRows() const noexcept;
	const uint32_t&& GetNumberOfColumns() const noexcept;

	void Print() const noexcept;

private:
	std::vector<std::vector<float>> m_Data;
};