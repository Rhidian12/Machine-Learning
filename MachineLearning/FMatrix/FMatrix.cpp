#include "FMatrix.h"
#include "../Utils/Utils.h"

#include <iostream>
#include <iomanip>

FMatrix::FMatrix(const uint32_t rows, const uint32_t cols, const float initValue)
	: m_Data{}
{
	Utils::Assert(rows == cols, "This FMatrix class only supports square matrices!");

	m_Data.reserve(rows);

	for (std::vector<float>& array : m_Data)
		array.reserve(cols);

	for (size_t i{}; i < rows; ++i)
		m_Data.push_back(std::vector<float>{});

	for (std::vector<float>& array : m_Data)
		for (size_t i{}; i < cols; ++i)
			array.push_back(initValue);
}

FMatrix::FMatrix(const FMatrix& other) noexcept
	: m_Data{ other.m_Data }
{
}

FMatrix::FMatrix(FMatrix&& other) noexcept
	: m_Data{ std::move(other.m_Data) }
{
	other.m_Data.clear();
}

FMatrix& FMatrix::operator=(const FMatrix& other) noexcept
{
	m_Data = other.m_Data;
	return *this;
}

FMatrix& FMatrix::operator=(FMatrix&& other) noexcept
{
	m_Data = std::move(other.m_Data);
	other.m_Data.clear();
	return *this;
}

void FMatrix::Set(const uint32_t row, const uint32_t col, const float value) noexcept
{
	Utils::Assert(row < m_Data.size() && col < m_Data.size(), "FMatrix::Get() > Index was out of bounds!");

	m_Data[row][col] = value;
}

const float FMatrix::Get(const uint32_t row, const uint32_t col) const noexcept
{
	Utils::Assert(row < m_Data.size() && col < m_Data.size(), "FMatrix::Get() > Index was out of bounds!");

	return m_Data[row][col];
}

void FMatrix::SetAll(const float value) noexcept
{
	for (std::vector<float>& array : m_Data)
		for (float& element : array)
			element = value;
}

void FMatrix::Print() const noexcept
{
	std::cout << std::fixed << std::setprecision(1);
	for (const std::vector<float>& array : m_Data)
	{
		for (const float element : array)
			std::cout << element << ", ";

		std::cout << std::endl;
	}
}
