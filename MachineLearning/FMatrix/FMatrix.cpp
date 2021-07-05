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
