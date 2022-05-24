#include <iostream>
#include "matrix.h"

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
	// basic matrix constr text
	int inputData1[16] = { 4, 3, 2, 6, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2, 6, 7 };
	mt::Matrix<int> testMatrix1(4, 4, inputData1);
	PrintMatrix(testMatrix1);

	std::cout << std::endl;
	std::cout << "Matrix + Matrix test" << std::endl;
	std::cout << std::endl;

	// matrix + matrix
	int inputData2[16] = { 4, 3, 2, 6, 5, 4, 3, 2, 1, 6, 54, 45, 36, 21, 62, 74 };
	mt::Matrix<int> testMatrix2(4, 4, inputData2);
	PrintMatrix(testMatrix1 + testMatrix2);

}