#include <iostream>
#include "matrix.h"

int main()
{
	int inputData[16] = { 4, 3, 2, 6, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2, 6, 7 };
	mt::Matrix<int> testMatrix(4, 4, inputData);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << testMatrix.getElement(i, j) << " ";
		}
		std::cout << std::endl;
	}
}