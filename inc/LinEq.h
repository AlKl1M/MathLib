#include "inc/matrix.h"
#include "inc/vector.h"

#include <vector>

#pragma once

// we making matrix to rowEchelone and then going from last element to make system of equations
template <class T>
mt::Vector<T> LinSolve(const mt::Matrix<T>* aMat, const mt::Vector<T>* bVec)
{
	mt::Matrix<T> inputMatrix = *aMat;
	int numDims = bVec->getNumDims();
	std::vector<T> VecData;
	for (int i = 0; i < numDims; i++)
		VecData.push_back(bVec->GetElement(i));
	mt::Matrix<T> bMat(numDims, 1, &VecData);
	inputMatrix.Join(bMat);
	mt::Matrix<T> EchelonMat = inputMatrix.RowEchelon();
	mt::Vector<T> output(VecData);

	int numRows = EchelonMat.GetNumRows();
	int numCols = EchelonMat.GetNumCols();
	int startRow = numRows - 1;

	for (int i = startRow; i >= 0; i--)
	{
		T tempResult = EchelonMat.getElement(i, numCols - 1);
		T sum = static_cast<T>(0.0);
		for (int j = i + 1; j < numRows; j++)
		{
			sum += (EchelonMat.getElement(i, j) * output.GetElement(j));
		}
		T result = (tempResult - sum) / EchelonMat.getElement(i, i);

		output.SetElement(i, result);
	}
	return output;
}