// MachineLearning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "FMatrix/FMatrix.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test FMatrix")
{
	FMatrix originalMatrix{ 4,4 };

	const uint32_t nrOfRows{ originalMatrix.GetNumberOfRows() };
	const uint32_t nrOfCols{ originalMatrix.GetNumberOfColumns() };

	REQUIRE(nrOfRows == 4);
	REQUIRE(nrOfCols == 4);

	for (uint32_t r{}; r < nrOfRows; ++r)
		for (uint32_t c{}; c < nrOfCols; ++c)
			REQUIRE(originalMatrix.Get(r, c) == 0.f);

	originalMatrix.Set(2, 2, 15.f);
	REQUIRE(originalMatrix.Get(2, 2) == 15.f);

	originalMatrix.SetAll(42.f);
	for (uint32_t r{}; r < nrOfRows; ++r)
		for (uint32_t c{}; c < nrOfCols; ++c)
			REQUIRE(originalMatrix.Get(r, c) == 42.f);

	FMatrix copyConstructorMatrix{ originalMatrix };
	REQUIRE(originalMatrix == copyConstructorMatrix);
	REQUIRE_FALSE(originalMatrix != copyConstructorMatrix);

	FMatrix moveConstructorMatrix{ std::move(copyConstructorMatrix) };
	REQUIRE(originalMatrix == moveConstructorMatrix);
	REQUIRE(copyConstructorMatrix.GetNumberOfRows() == 0);

	FMatrix copyOperatorMatrix{ originalMatrix };
	REQUIRE(originalMatrix == copyOperatorMatrix);

	FMatrix moveOperatorMatrix{ std::move(copyOperatorMatrix) };
	REQUIRE(originalMatrix == moveOperatorMatrix);
	REQUIRE(copyOperatorMatrix.GetNumberOfRows() == 0);
}

//int main()
//{
//	FMatrix matrix{ 4,4 };
//
//	matrix.Print();
//
//	matrix.Set(0, 0, 10.f);
//
//	matrix.Print();
//
//	return 0;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
