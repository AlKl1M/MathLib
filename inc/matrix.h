#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>û

namespace mt {
	template <class T>
	class Matrix {
	public:
		Matrix();
		Matrix(int Row, int Col);
		Matrix(int Row, int Col, const T* Data);
		Matrix(const Matrix<T>& matrix);
		Matrix(int Row, int Col, const std::vector<T>* Data);

		~Matrix();

		T getElement(int Row, int Col) const;
		bool SetElement(int Row, int Col, T value);
		int GetNumRows() const;
		int GetNumCols() const;

		template <class T> friend Matrix<T> operator+ (const Matrix<T>& leftM, const Matrix<T>& rightM);
		template <class T> friend Matrix<T> operator+ (const T& leftEl, const Matrix<T>& rightM);
		template <class T> friend Matrix<T> operator+ (const Matrix<T>& leftM, const T& rightEl);

		template <class T> friend Matrix<T> operator- (const Matrix<T>& leftM, const Matrix<T>& rightM);
		template <class T> friend Matrix<T> operator- (const T& leftEl, const Matrix<T>& rightM);
		template <class T> friend Matrix<T> operator- (const Matrix<T>& leftM, const T& rightEl);

		template <class T> friend Matrix<T> operator* (const Matrix<T>& leftM, const Matrix<T>& rightM);
		template <class T> friend Matrix<T> operator* (const T& leftEl, const Matrix<T>& rightM);
		template <class T> friend Matrix<T> operator* (const Matrix<T>& leftM, const T& rightEl);

		bool operator== (const Matrix<T>& rightM);
		Matrix<T> FindSubMatrix(int Row, int Col);
		T Determinant();
		Matrix<T> transposition();
		bool Resize(int numRows, int numCols);
		bool Inverse();
		bool Separate(Matrix<T>& matrix1, Matrix<T>& matrix2, int colNum);
		Matrix<T> RowEchelon();
	private:
		bool IsSquare();
		bool CloseEnough(T f, T g);
		void SwapRow(int i, int j);
		void MultAdd(int i, int j, T multFactor); // j * multFactor + i
		void MultRow(int i, T multFactor);  // i * multFactor
		bool Join(const Matrix<T>& matrix2); // concatination
		int Sub2Ind(int row, int col) const;
		int FindRowWithMaxElement(int colNumber, int startingRow); // from starting row in colNumber it search max
		void PrintMatrix();
		void SetToIdentity();
		bool isRowEchelon();
		

	private:
		T* m_matrixData;
		int m_Row, m_Col, m_Elements;
	};

	template <class T>
	// Base constructor - 1x1 all zeros 
	Matrix<T>::Matrix()
	{
		m_Row = 1;
		m_Col = 1;
		m_Elements = 1;
		m_matrixData = nullptr;
	}

	// Rows x Columns matrix with all zeros
	template <class T>
	Matrix<T>::Matrix(int Row, int Col) 
	{
		m_Row = Row;
		m_Col = Col;
		m_Elements = m_Row * m_Col;
		m_matrixData = new T[m_Elements];
		for (int i = 0; i < m_Elements; i++)
			m_matrixData[i] = 0.0;
	}

	// Rows x Columns matrix with input Data
	template <class T>
	Matrix<T>::Matrix(int Row, int Col, const T* Data)
	{
		m_Row = Row;
		m_Col = Col;
		m_Elements = m_Row * m_Col;
		m_matrixData = new T[m_Elements];
		for (int i = 0; i < m_Elements; i++)
			m_matrixData[i] = Data[i];
	}

	// copy constructor
	template <class T>
	Matrix<T>::Matrix(const Matrix<T>& matrix)
	{
		m_Row = matrix.m_Row;
		m_Col = matrix.m_Col;
		m_Elements = matrix.m_Elements;

		m_matrixData = new T[m_Elements];
		for (int i = 0; i < m_Elements; i++)
			m_matrixData[i] = matrix.m_matrixData[i];
	}

	template <class T>
	Matrix<T>::Matrix(int Row, int Col, const std::vector<T>* Data)
	{
		m_Row = Row;
		m_Col = Col;
		m_Elements = m_Row * m_Col;
		m_matrixData = new T[m_Elements];
		for (int i = 0; i < m_Elements; i++)
			m_matrixData[i] = Data->at(i);
	}

	// Destructor
	template <class T>
	Matrix<T>::~Matrix()
	{
		if (m_matrixData) {
			delete[] m_matrixData;
		}
		m_matrixData = nullptr;
	}

	// Getter
	template <class T>
	T Matrix<T>::getElement(int Row, int Col) const
	{
		int l = Sub2Ind(Row, Col);
		if (l >= 0)
			return m_matrixData[l];
		else
			return 0.0;
	}

	// Setter
	template <class T>
	bool Matrix<T>::SetElement(int Row, int Col, T value) 
	{
		int l = Sub2Ind(Row, Col);

		if (l >= 0) {
			m_matrixData[l] = value;
			return true;
		}
		else
			return false;
	}

	template <class T>
	int Matrix<T>::GetNumRows() const
	{
		return m_Row;
	}

	template <class T>
	int Matrix<T>::GetNumCols() const
	{
		return m_Col;
	}

	// overload for matrix + matrix
	template <class T>
	Matrix<T> operator+ (const Matrix<T>& leftM, const Matrix<T>& rightM)
	{
		int nRows = leftM.m_Row;
		int nCols = leftM.m_Col;
		int Elements = nRows * nCols;
		T* temp = new T[Elements];
		for (int i = 0; i < Elements; i++)
			temp[i] = leftM.m_matrixData[i] + rightM.m_matrixData[i];
		Matrix<T> result(nRows, nCols, temp);
		delete[] temp;
		return result;
	}

	template <class T>
	Matrix<T> operator+ (const T& leftEl, const Matrix<T>& rightM)
	{
		int nRows = rightM.m_Row;
		int nCols = rightM.m_Col;
		int Elements = nRows * nCols;
		T* temp = new T[Elements];
		for (int i = 0; i < Elements; i++)
			temp[i] = leftEl + rightM.m_matrixData[i];
		Matrix<T> result(nRows, nCols, temp);
		delete[] temp;
		return result;
	}

	template <class T>
	Matrix<T> operator+ (const Matrix<T>& leftM, const T& rightEl)
	{
		int nRows = leftM.m_Row;
		int nCols = leftM.m_Col;
		int Elements = nRows * nCols;
		T* temp = new T[Elements];
		for (int i = 0; i < Elements; i++)
			temp[i] = leftM.m_matrixData[i] + rightEl;
		Matrix<T> result(nRows, nCols, temp);
		delete[] temp;
		return result;
	}

	template <class T>
	Matrix<T> operator- (const Matrix<T>& leftM, const Matrix<T>& rightM)
	{
		int nRows = leftM.m_Row;
		int nCols = leftM.m_Col;
		int Elements = nRows * nCols;
		T* temp = new T[Elements];
		for (int i = 0; i < Elements; i++)
			temp[i] = leftM.m_matrixData[i] - rightM.m_matrixData[i];
		Matrix<T> result(nRows, nCols, temp);
		delete[] temp;
		return result;
	}

	template <class T>
	Matrix<T> operator- (const T& leftEl, const Matrix<T>& rightM)
	{
		int nRows = rightM.m_Row;
		int nCols = rightM.m_Col;
		int Elements = nRows * nCols;
		T* temp = new T[Elements];
		for (int i = 0; i < Elements; i++)
			temp[i] = leftEl - rightM.m_matrixData[i];
		Matrix<T> result(nRows, nCols, temp);
		delete[] temp;
		return result;
	}

	template <class T>
	Matrix<T> operator- (const  Matrix<T>& leftM, const T& rightEl)
	{
		int nRows = leftM.m_Row;
		int nCols = leftM.m_Col;
		int Elements = nRows * nCols;
		T* temp = new T[Elements];
		for (int i = 0; i < Elements; i++)
			temp[i] = leftM.m_matrixData[i] - rightEl;
		Matrix<T> result(nRows, nCols, temp);
		delete[] temp;
		return result;
	}

	template <class T>
	Matrix<T> operator* (const T& leftEl, const Matrix<T>& rightM)
	{
		int nRow = rightM.m_Row;
		int nCol = rightM.m_Col;
		int numElements = nRow * nCol;
		T* temp = new T[numElements];
		for (int i = 0; i < numElements; ++i)
			temp[i] = leftEl * rightM.m_matrixData[i];
		Matrix<T> result(nRow, nCol, temp);
		delete[] temp;
		return result;
	}

	template <class T>
	Matrix<T> operator* (const Matrix<T>& leftM, const T& rightEl)
	{
		int nRow = leftM.m_Row;
		int nCol = leftM.m_Col;
		int numElements = nRow * nCol;
		T* temp = new T[numElements];
		for (int i = 0; i < numElements; ++i)
			temp[i] = leftM.m_matrixData[i] * rightEl;
		Matrix<T> result(nRow, nCol, temp);
		delete[] temp;
		return result;
	}

	template <class T>
	Matrix<T> operator* (const Matrix<T>& leftM, const Matrix<T>& rightM)
	{
		int r_nRows = rightM.m_Row;
		int r_nCols = rightM.m_Col;
		int l_nRows = leftM.m_Row;
		int l_nCols = leftM.m_Col;

		if (l_nCols == r_nRows)
		{
			T* temp = new T[leftM.m_Row * rightM.m_Col];
			// going through the rows
			for (int i = 0; i < l_nRows; i++)
			{
				// going through the cols - result must be the same size as r and c
				for (int j = 0; j < r_nCols; j++)
				{
					T elementResult = static_cast<T>(0.0);
					// going through each element of leftM row
					for (int k = 0; k < l_nCols; k++)
					{
						int leftLinearIndex = (i * l_nCols) + k; // (row * numCols) + col (r = 0; c = 0; numCols = 3 lI = 0)
						int rightLinearIndex = (k * r_nCols) + j; // (row * numCols) + col
						elementResult += (leftM.m_matrixData[leftLinearIndex] * rightM.m_matrixData[rightLinearIndex]); // sum of r and c
					}
					int resultIndex = (i * r_nCols) + j; // (row * numCols) + col
					temp[resultIndex] = elementResult;
				}
			}
			Matrix<T> result(l_nRows, r_nCols, temp);
			delete[] temp;
			return result;
		}
		else
		{
			Matrix<T> result(1, 1);
			return result;
		}
	}

	template <class T>
	bool Matrix<T>:: operator== (const Matrix<T>& rightM)
	{
		if ((this->m_Row != rightM.m_Col) && (this->m_Col != rightM.m_Col))
			return false;
		bool flag = true;
		for (int i = 0; i < this->m_Elements; i++)
		{
			if (this->m_matrixData[i] != rightM.m_matrixData[i])
				flag = false;
		}
		return flag;
	}

	template <class T>
	Matrix<T> Matrix<T>::FindSubMatrix(int Row, int Col) 
	{
		Matrix<T> subMatrix(m_Row - 1, m_Col - 1);
		int count = 0;
		for (int i = 0; i < m_Row; i++)
		{
			for (int j = 0; j < m_Col; j++)
			{
				if ((i != Row) && (j != Col))
				{
					subMatrix.m_matrixData[count] = this->getElement(i, j);
					count++;
				}
			}
		}
		return subMatrix;
	}

	template <class T>
	T Matrix<T>::Determinant()
	{
		if (m_Col != m_Row)
		{
			throw std::invalid_argument("matrix is not square => cant find the determinant");
		}

		T determinant;
		if (m_Row == 2)
		{
			return (m_matrixData[0] * m_matrixData[3]) - (m_matrixData[1] * m_matrixData[2]); // basic situation for 2x2
		}
		T sum = 0.0;
		T sign = 1.0;
		for (int i = 0; i < m_Col; ++i)
		{
			Matrix<T> subMatrix = this->FindSubMatrix(0, i);
			sum += sign * this->getElement(0, i) * subMatrix.Determinant(); // // -1^(r+c) * MINOR
			sign = -sign;
		}
		determinant = sum;
		return determinant;
	}

	template <class T>
	Matrix<T> Matrix<T>::transposition()
	{
		int n_Row = m_Row;
		int n_Col = m_Col;;
		Matrix<T> temp(n_Row, n_Col);
		for (int i = 0; i < n_Row; i++)
		{
			for (int j = 0; j < n_Col; j++)
			{
				temp.SetElement(i, j, this->getElement(j, i));
			}
		}
		return temp;
	}

	template <class T>
	bool Matrix<T>::CloseEnough(T f, T g)
	{
		return fabs(f - g) < 1e-9; // how close to 0
	}

	template <class T>
	bool Matrix<T>::Resize(int numRows, int numCols)
	{
		m_Row = numRows;
		m_Col = numCols;
		m_Elements = (m_Row * m_Col);
		delete[] m_matrixData;
		m_matrixData = new T[m_Elements];
		if (m_matrixData != nullptr)
		{
			for (int i = 0; i < m_Elements; i++) {
				m_matrixData[i] = 0.0;
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	// separate matrix to 2 matrices from nCol
	template <class T>
	bool Matrix<T>::Separate(Matrix<T>& matrix1, Matrix<T>& matrix2, int nCol)
	{
		int nRow = m_Row;
		int nCol1 = nCol;
		int nCol2 = m_Col - nCol;

		matrix1.Resize(nRow, nCol1);
		matrix2.Resize(nRow, nCol1);

		for (int i = 0; i < m_Row; i++)
		{
			for (int j = 0; j < m_Col; j++)
			{
				if (j < nCol)
				{
					matrix1.SetElement(i, j, this->getElement(i, j));
				}
				else
				{
					matrix2.SetElement(i, j - nCol, this->getElement(i, j));
				}
			}
			return true;
		}
	}

	template <class T>
	bool Matrix<T>::Join(const Matrix<T>& matrix2)
	{
		int n_Row1 = m_Row;
		int n_Row2 = matrix2.m_Row;
		int n_Col1 = m_Col;
		int n_Col2 = matrix2.m_Col;

		if (n_Row1 != n_Row2)
			throw std::invalid_argument("You can not join matrices with different numbers of rows");

		// concatinate data
		T* newData = new T[n_Row1 * (n_Col1 + n_Col2)];

		int index, resultIndex;
		for (int i = 0; i < n_Row1; i++)
		{
			for (int j = 0; j < (n_Col1 + n_Col2); j++)
			{
				resultIndex = (i * (n_Col1 + n_Col2)) + j;

				if (j < n_Col1)
				{
					index = (i * n_Col1) + j;
					newData[resultIndex] = m_matrixData[index];
				}
				else
				{
					index = (i * n_Col2) + (j - n_Col1);
					newData[resultIndex] = matrix2.m_matrixData[index];
				}
			}
		}
		m_Col = n_Col1 + n_Col2;
		m_Elements = m_Row * m_Col;
		delete[] m_matrixData;
		m_matrixData = new T[m_Elements];
		for (int i = 0; i < m_Elements; i++)
			m_matrixData[i] = newData[i];
		
		delete[] newData;
		return true;
	}

	// method to get right RxC position of element from array
	template <class T>
	int Matrix<T>::Sub2Ind(int row, int col) const
	{
		if ((row < m_Row) && (row >= 0) && (col < m_Col) && (col >= 0))
			return (row * m_Col) + col;
		else
			return -1;
	}

	template <class T>
	void Matrix<T>::SwapRow(int i, int j)
	{
		T* tempR = new T[m_Col];
		for (int k = 0; k < m_Col; k++)
			tempR[k] = m_matrixData[Sub2Ind(i, k)];

		for (int k = 0; k < m_Col; k++)
			m_matrixData[Sub2Ind(i, k)] = m_matrixData[Sub2Ind(j, k)];

		for (int k = 0; k < m_Col; k++)
			m_matrixData[Sub2Ind(j, k)] = tempR[k];

		delete[] tempR;
	}

	template <class T>
	void Matrix<T>::MultAdd(int i, int j, T multFactor)
	{
		for (int k = 0; k < m_Col; k++)
			m_matrixData[Sub2Ind(i, k)] += (m_matrixData[Sub2Ind(j, k)] * multFactor);
	}

	template <class T>
	int Matrix<T>::FindRowWithMaxElement(int colNumber, int startingRow)
	{
		T temp = m_matrixData[Sub2Ind(startingRow, colNumber)];
		int rowIndex = startingRow;
		for (int i = startingRow + 1; i < m_Row; i++)
		{
			if (fabs(m_matrixData[Sub2Ind(i, colNumber)]) > fabs(temp))
			{
				rowIndex = i;
				temp = m_matrixData[Sub2Ind(i, colNumber)];
			}
		}
		return rowIndex;
	}

	template <class T>
	void Matrix<T>::MultRow(int i, T multFactor)
	{
		for (int k = 0; k < m_Col; k++)
			m_matrixData[Sub2Ind(i, k)] *= multFactor;
	}

	template <class T>
	bool Matrix<T>::IsSquare()
	{
		if (m_Col == m_Row)
			return true;
		else
			return false;
	}

	// method to make any matrix identity
	template <class T>
	void Matrix<T>::SetToIdentity()
	{
		if (!IsSquare())
			throw std::invalid_argument("Matrix is not square");

		for (int i = 0; i < m_Row; i++)
		{
			for (int j = 0; j < m_Col; j++)
			{
				if (i == j)
					m_matrixData[Sub2Ind(i, j)] = 1.0;
				else
					m_matrixData[Sub2Ind(i, j)] = 0.0;
			}
		}
	}

	template <class T>
	bool Matrix<T>::Inverse()
	{
		if (!IsSquare())
			throw std::invalid_argument("Operation does not support matrix that doesnt square");

		Matrix<T> identityMatrix(m_Row, m_Col);
		identityMatrix.SetToIdentity();
		int originalNumCols = m_Col;
		// if matrix is square then we concat it with identity matrix
		Join(identityMatrix);
		int cRow, cCol;
		// we use this maxCount to don't allow infinite cycle
		int maxCount = 100;
		int count = 0;
		bool flag = false;
		while ((!flag) && (count < maxCount))
		{
			// first we going though diagonals
			for (int i = 0; i < m_Row; i++)
			{
				cRow = i;
				cCol = i;

				int maxIndex = FindRowWithMaxElement(cCol, cRow); // next we finding row with max element in cCol

				if (maxIndex != cRow) // if that doesnt current row we swap them
				{
					SwapRow(cRow, maxIndex);
				}

				if (m_matrixData[Sub2Ind(cRow, cCol)] != 1.0)
				{
					T mult = 1.0 / m_matrixData[Sub2Ind(cRow, cCol)]; // 1.0 / currentElement
					MultRow(cRow, mult);
				}

				// going though all rows of this column
				for (int j = cRow + 1; j < m_Row; j++)
				{
					if (!CloseEnough(m_matrixData[Sub2Ind(j, cCol)], 0.0))
					{
						int rowOneIndex = cCol;
						// value at the current element
						T currentElementValue = m_matrixData[Sub2Ind(j, cCol)];
						// get the value at (rowOneIndex and cCol)
						T rowOneValue = m_matrixData[Sub2Ind(rowOneIndex, cCol)];

						// if that close to zero then we move
						if (!CloseEnough(rowOneValue, 0.0))
						{
							T correctionFactor = -(currentElementValue / rowOneValue);
							MultAdd(j, rowOneIndex, correctionFactor); // rowOneIndex * cF + j
						}
					}
				}
				for (int k = cCol + 1; k < originalNumCols; k++)
				{
					if (!CloseEnough(m_matrixData[Sub2Ind(cRow, k)], 0.0))
					{
						int rowOneIndex = k;
						T currentElementValue = m_matrixData[Sub2Ind(cRow, k)];
						T rowOneValue = m_matrixData[Sub2Ind(rowOneIndex, k)];
						if (!CloseEnough(rowOneValue, 0.0))
						{
							T correctionFactor = -(currentElementValue / rowOneValue);
							MultAdd(cRow, rowOneIndex, correctionFactor);
						}
					}
				}
			}
			Matrix<T> left;
			Matrix<T> right;
			this->Separate(left, right, originalNumCols);

			if (left == identityMatrix)
			{
				flag = true;

				m_Col = originalNumCols;
				m_Elements = m_Row * m_Col;
				delete[] m_matrixData;
				m_matrixData = new T[m_Elements];
				for (int i = 0; i < m_Elements; i++)
					m_matrixData[i] = right.m_matrixData[i];
			}
			count++;
		}
		return flag;
	}

	template <class T>
	bool Matrix<T>::isRowEchelon()
	{
		T sum = static_cast<T>(0.0);
		for (int i = 0; i < m_Row; i++)
		{
			for (int j = 0; j < m_Col; j++)
			{
				sum += m_matrixData[Sub2Ind(i, j)];
			}
		}
		return CloseEnough(sum, 0.0); // sum should be 0 because sum is out upper-diagonal elements
	}
	
	template <class T>
	Matrix<T> Matrix<T>::RowEchelon()
	{
		if (m_Col < m_Row)
			throw std::invalid_argument("The matrix should have at least as many cols as rows");

		T* temp;
		temp = new T[m_Row * m_Col];
		for (int i = 0; i < (m_Row * m_Col); i++)
		{
			temp[i] = m_matrixData[i];
		}

		int cRow, cCol;
		int maxCount = 100; // we want to prevent infinite cycle
		int count = 0;
		bool flag = false;
		while ((!flag) && (count < maxCount))
		{
			for (int i = 0; i < m_Row; i++)
			{
				cRow = i;
				cCol = i;
				int max = FindRowWithMaxElement(cCol, cRow);
				// going through rows
				for (int j = cRow + 1; j < m_Row; j++)
				{
					if (!CloseEnough(m_matrixData[Sub2Ind(j, cCol)], 0.0))
					{
						int rowIndex = cCol;
						T currentEl = m_matrixData[Sub2Ind(j, cCol)];
						T rowEl = m_matrixData[Sub2Ind(rowIndex, cCol)];
						if (!CloseEnough(rowEl, 0.0))
						{
							T fix = -(currentEl / rowEl);
							MultAdd(j, rowIndex, fix);
						}
					}
				}
			}
			flag = this->isRowEchelon();
			count++;
		}
		Matrix<T> result(m_Row, m_Col, m_matrixData);
		return result;
	}
} 