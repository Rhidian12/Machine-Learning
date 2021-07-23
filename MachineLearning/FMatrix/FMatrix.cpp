#include "FMatrix.h"
#include "../Utils/Utils.h"

#include <iostream> // std::cout
#include <iomanip> // std::fixed, std::setprecision

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

const uint32_t&& FMatrix::GetNumberOfRows() const noexcept
{
	return std::move(m_Data.size());
}

const uint32_t&& FMatrix::GetNumberOfColumns() const noexcept
{
	return std::move(m_Data[0].size());
}

const float&& FMatrix::GetSum() const noexcept
{
	float sum{};
	for (size_t r{}; r < GetNumberOfRows(); ++r)
		for (size_t c{}; c < GetNumberOfColumns(); ++c)
			sum += m_Data[r][c];

	return std::move(sum);
}

const float&& FMatrix::GetMax() const noexcept
{
	float max{};
	for (size_t r{}; r < GetNumberOfRows(); ++r)
		for (size_t c{}; c < GetNumberOfColumns(); ++c)
			if (m_Data[r][c] > max)
				max = m_Data[r][c];

	return std::move(max);
}

const float&& FMatrix::GetMaxOfRow(const float row) const noexcept
{
	float max{};
	for (size_t c{}; c < GetNumberOfColumns(); ++c)
		if (m_Data[row][c] > max)
			max = m_Data[row][c];

	return std::move(max);
}

void FMatrix::Print() const noexcept
{
	std::cout << std::fixed << std::setprecision(1);
	for (const std::vector<float>& array : m_Data)
	{
		for (const float element : array)
			std::cout << element << "," << std::setw(6);

		std::cout << std::setw(0);
		std::cout << std::endl;
	}
}

const bool FMatrix::operator==(const FMatrix& other) const noexcept
{
	Utils::Assert(GetNumberOfRows() == other.GetNumberOfRows(), "FMatrix::operator==() > Matrices don't have the same amount of rows!\n");
	Utils::Assert(GetNumberOfColumns() == other.GetNumberOfColumns(), "FMatrix::operator==() > Matrices don't have the same amount of columns!\n");

	for (size_t r{}; r < m_Data.size(); ++r)
		for (size_t c{}; c < m_Data[r].size(); ++c)
			if (m_Data[r][c] != other.m_Data[r][c])
				return false;

	return true;
}

const bool FMatrix::operator!=(const FMatrix& other) const noexcept
{
	Utils::Assert(GetNumberOfRows() == other.GetNumberOfRows(), "FMatrix::operator!=() > Matrices don't have the same amount of rows!\n");
	Utils::Assert(GetNumberOfColumns() == other.GetNumberOfColumns(), "FMatrix::operator!=() > Matrices don't have the same amount of columns!\n");
	return !(*this == other);
}
