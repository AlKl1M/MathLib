#include <iostream>
#include "inc/matrix.h"
#include "inc/vector.h"
#include "inc/LinEq.h"
#include <vector>

int main()
{
	int inputData1[16] = { 4, 3, 24, 3, 
		21, 4, 44, 32, 
		9, 2, 4, 5, 
		3, 4, 44, 3};
	int inputData2[16] = { 4, 3, 4, 6, 
		44, 23, 11, 2, 
		6, 55, 43, 2, 
		12, 3, 24, 4 };
	mt::Matrix<int> testMatrix1(4, 4, inputData1);
	mt::Matrix<int> testMatrix2(4, 4, inputData2);
	
	std::cout << std::endl;
	std::cout << "Matrix1" << std::endl;
	std::cout << std::endl;

	std::cout << testMatrix1 << std::endl;

	std::cout << std::endl;
	std::cout << "Matrix2" << std::endl;
	std::cout << std::endl;
	std::cout << testMatrix2 << std::endl;

	std::cout << std::endl;
	std::cout << "Matrix + Matrix test" << std::endl;
	std::cout << std::endl;
	
	std::cout << testMatrix1 + testMatrix2 << std::endl;

	std::cout << std::endl;
	std::cout << "Matrix + num test" << std::endl;
	std::cout << std::endl;
	std::cout << testMatrix1 + 4 << std::endl;

	std::cout << std::endl;
	std::cout << "num + Matrix test" << std::endl;
	std::cout << std::endl;
	std::cout << 4 + testMatrix1 << std::endl;

	std::cout << std::endl;
	std::cout << "Matrix - Matrix test" << std::endl;
	std::cout << std::endl;
	std::cout << testMatrix1 - testMatrix2 << std::endl;

	std::cout << std::endl;
	std::cout << "Matrix - num test" << std::endl;
	std::cout << std::endl;
	std::cout << testMatrix1 - 5 << std::endl;

	std::cout << std::endl;
	std::cout << "Num - matrix test" << std::endl;
	std::cout << std::endl;
	std::cout << 5 - testMatrix1 << std::endl;

	std::cout << std::endl;
	std::cout << "Matrix * num test" << std::endl;
	std::cout << std::endl;
	std::cout << testMatrix1 * 5 << std::endl;

	std::cout << std::endl;
	std::cout << "Num * matrix test" << std::endl;
	std::cout << std::endl;
	std::cout << 5 * testMatrix1 << std::endl;

	std::cout << std::endl;
	std::cout << "Matrix * matrix test" << std::endl;
	std::cout << std::endl;
	std::cout << testMatrix1 * testMatrix2 << std::endl;

	std::cout << std::endl;
	std::cout << "Submatrix test" << std::endl;
	std::cout << std::endl;

	std::cout << testMatrix1.FindSubMatrix(1, 1) << std::endl;

	std::cout << std::endl;
	std::cout << "Determinant test" << std::endl;
	std::cout << std::endl;

	std::cout << testMatrix1.Determinant() << std::endl;

	std::cout << std::endl;
	std::cout << "Transposition test" << std::endl;
	std::cout << std::endl;

	std::cout << testMatrix1.transposition() << std::endl;

	std::cout << std::endl;
	std::cout << "Inverse test" << std::endl;
	std::cout << std::endl;

	double inverTestData2[9] = { 1.0 , 3.0, -5.0,
	0.0, 1.0, 2.0,
	0.0, 0.0, 1.0};
	mt::Matrix<double> invertTest(3, 3, inverTestData2);
	mt::Matrix<double> invertResult = invertTest;
	invertResult.Inverse();
	std::cout << invertResult << std::endl;

	std::cout << std::endl;
	std::cout << "RowEchelon test" << std::endl;
	std::cout << std::endl;

	double testData3[16] = {3.0, 0.0, 1.0, -1.0, 
		1.0, 5.0, 1.0, 0.0, 
		0.0, 1.0, -1.0, -1.0,
		-1.0, 1.0, 1.0, 1.0};
	mt::Matrix<double> testMatrix3(4, 4, testData3);
	mt::Matrix<double> testRowEchelon = testMatrix3.RowEchelon();
	std::cout << testRowEchelon << std::endl;

	std::cout << std::endl;
	std::cout << "Vector creation test" << std::endl;
	std::cout << std::endl;

	std::vector<double> testData4 = { 13.0, 9.0, -6.0};
	mt::Vector<double> bVec{ testData4 };
	std::cout << bVec << std::endl;

	std::cout << std::endl;
	std::cout << "Vector creation test" << std::endl;
	std::cout << std::endl;

	std::vector<double> testData5 = { 4.0, 2.0, -4.0 };
	mt::Vector<double> cVec{ testData5 };
	std::cout << cVec << std::endl;

	std::cout << std::endl;
	std::cout << "Vector + vector test" << std::endl;
	std::cout << std::endl;

	std::cout << bVec + cVec << std::endl;

	std::cout << std::endl;
	std::cout << "Vector - vector test" << std::endl;
	std::cout << std::endl;

	std::cout << bVec - cVec << std::endl;

	std::cout << std::endl;
	std::cout << "Vector * num test" << std::endl;
	std::cout << std::endl;

	std::cout << bVec * 4 << std::endl;

	std::cout << std::endl;
	std::cout << "SLAU test" << std::endl;
	std::cout << std::endl;


	std::cout << std::endl;
	std::cout << "ORIGINAL" << std::endl;
	std::cout << std::endl;

	double simpleData[12] = {1.0, 3.0, -1.0, 
		13.0, 4.0, -1.0, 
		1.0, 9.0, 2.0, 
		4.0, 3.0, -6.0};
	mt::Matrix<double> testMatrix4(3, 4, simpleData);
	std::cout << testMatrix4 << std::endl;

	std::cout << std::endl;
	std::cout << "ROW ECHELONE TEST" << std::endl;
	std::cout << std::endl;

	mt::Matrix<double> rowEchelonTest = testMatrix4.RowEchelon();
	std::cout << rowEchelonTest << std::endl;

	std::cout << std::endl;
	std::cout << "SLAU 1 TEST" << std::endl;
	std::cout << "AX = B WHERE A EQUAL TO" << std::endl;
	std::cout << std::endl;

	double simpleData2[9] = { 4.0, 3.0, -7.0, 
		6.0, -5.0, 1.0,
		2.0, 42.0, 3.0 };
	mt::Matrix<double> aMat(3, 3, simpleData2);
	std::cout << aMat << std::endl;

	std::cout << std::endl;
	std::cout << "AX = B WHERE B EQUAL TO" << std::endl;
	std::cout << std::endl;

	std::vector<double> vectorData{ 4.0, 3.0, -6.0 };
	mt::Vector<double> gVec{ vectorData };
	std::cout << gVec << std::endl;

	std::cout << std::endl;
	std::cout << "SO FINAL LIN SOLVE LOOKS LIKE" << std::endl;
	std::cout << std::endl;

	mt::Vector<double> tResult = LinSolve<double>(&aMat, &gVec);
	std::cout << tResult << std::endl;

	std::cout << std::endl;
	std::cout << "SLAU 1 TEST" << std::endl;
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << "SLAU 1 TEST" << std::endl;
	std::cout << "AX = B WHERE A EQUAL TO" << std::endl;
	std::cout << std::endl;

	double mattest2[9] = { 4.0, -3.0, 18.0, 
		2.0, 1.0, 6.0, 
		1.0, -1.0, 5.0 };
	mt::Matrix<double> testMatrix5(3, 3, mattest2);
	std::cout << testMatrix5 << std::endl;
	
	std::cout << std::endl;
	std::cout << "AX = B WHERE B EQUAL TO" << std::endl;
	std::cout << std::endl;

	std::vector<double> vectorData2{ 45.0, 19.0, 12.0 };
	mt::Vector<double> eVec{ vectorData2 };
	std::cout << eVec << std::endl;

	std::cout << std::endl;
	std::cout << "SO FINAL LIN SOLVE LOOKS LIKE" << std::endl;
	std::cout << std::endl;

	mt::Vector<double> tResult2 = LinSolve<double>(&testMatrix5, &eVec);
	std::cout << tResult2 << std::endl;
}