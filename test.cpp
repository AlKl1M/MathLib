#include <iostream>
#include "inc/matrix.h"

template <class T>
void PrintMatrix(mt::Matrix<T> matrix)
{
	int n_R = matrix.GetNumRows();
	int n_C = matrix.GetNumCols();
	for (int i = 0; i < n_R; i++) {
		for (int j = 0; j < n_C; j++)
		{
			std::cout << matrix.getElement(i, j) << " ";
		}
	std::cout << std::endl;
	}
}

int main()
{
	int inputData1[16] = { 4, 3, 24, 3, 21, 4, 44, 32, 9, 2, 4, 5, 3, 4, 44, 3};
	int inputData2[16] = { 4, 3, 4, 6, 44, 23, 11, 2, 6, 55, 43, 2, 12, 3, 24, 4 };
	mt::Matrix<int> testMatrix1(4, 4, inputData1);
	mt::Matrix<int> testMatrix2(4, 4, inputData2);
	PrintMatrix(testMatrix1);

	std::cout << std::endl;
	PrintMatrix(testMatrix2);

	std::cout << std::endl;
	std::cout << "Matrix + Matrix test" << std::endl;
	std::cout << std::endl;
	
	PrintMatrix(testMatrix1 + testMatrix2);

	std::cout << std::endl;
	std::cout << "Matrix + num test" << std::endl;
	std::cout << std::endl;
	PrintMatrix(testMatrix1 + 4);

	std::cout << std::endl;
	std::cout << "num + Matrix test" << std::endl;
	std::cout << std::endl;
	PrintMatrix(4 + testMatrix1);

	std::cout << std::endl;
	std::cout << "Matrix - Matrix test" << std::endl;
	std::cout << std::endl;
	PrintMatrix(testMatrix1 - testMatrix2);

	std::cout << std::endl;
	std::cout << "Matrix - num test" << std::endl;
	std::cout << std::endl;
	PrintMatrix(testMatrix1 - 5);

	std::cout << std::endl;
	std::cout << "Num - matrix test" << std::endl;
	std::cout << std::endl;
	PrintMatrix(5 - testMatrix1);

	std::cout << std::endl;
	std::cout << "Matrix * num test" << std::endl;
	std::cout << std::endl;
	PrintMatrix(testMatrix1 * 5);

	std::cout << std::endl;
	std::cout << "Num * matrix test" << std::endl;
	std::cout << std::endl;
	PrintMatrix(5 * testMatrix1);

	std::cout << std::endl;
	std::cout << "Matrix * matrix test" << std::endl;
	std::cout << std::endl;
	PrintMatrix(testMatrix1 * testMatrix2);

	std::cout << std::endl;
	std::cout << "Submatrix test" << std::endl;
	std::cout << std::endl;

	PrintMatrix(testMatrix1.FindSubMatrix(1, 1));

	std::cout << std::endl;
	std::cout << "Determinant test" << std::endl;
	std::cout << std::endl;

	std::cout << testMatrix1.Determinant() << std::endl;

	std::cout << std::endl;
	std::cout << "Transposition test" << std::endl;
	std::cout << std::endl;

	PrintMatrix(testMatrix1.transposition());

	std::cout << std::endl;
	std::cout << "Inverse test" << std::endl;
	std::cout << std::endl;

	double inverTestData2[9] = { 1.0 , 3.0, -5.0,
	0.0, 1.0, 2.0,
	0.0, 0.0, 1.0};
	mt::Matrix<double> invertTest(3, 3, inverTestData2);
	mt::Matrix<double> invertResult = invertTest;
	invertResult.Inverse();
	PrintMatrix(invertResult);
}