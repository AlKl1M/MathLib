#pragma once

#include <iostream>

namespace mt {
	template <class T>
	class Matrix {
	public:
		Matrix();
		Matrix(int Row, int Col);
		Matrix(int Row, int Col, const T* Data);
		Matrix(const Matrix<T>& matrix);

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
		int l = 0;
		if ((Row < m_Row) && (Row >= 0) && (Col < m_Col) && (Col >= 0))
			l = (Row * m_Col) + Col;
		else
			l = -1;

		if (l >= 0)
			return m_matrixData[l];
		else
			return 0.0;
	}

	// Setter
	template <class T>
	bool Matrix<T>::SetElement(int Row, int Col, T value) {
		int l = 0;
		if ((Row < m_Row) && (Row >= 0) && (Col < m_Col) && (Col >= 0))
			l = (Row * m_Col) + Col;
		else
			l = -1;
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
		int r_numRows = rightM.m_Row;
		int r_numCols = rightM.m_Col;
		int l_numRows = leftM.m_Row;
		int l_numCols = leftM.m_Col;

		if (l_numCols == r_numRows)
		{
			T* tempResult = new T[leftM.m_Row * rightM.m_Col];
			// going through the rows
			for (int i = 0; i < l_numRows; i++)
			{
				// going through the cols - result must be the same size as r and c
				for (int j = 0; j < r_numCols; j++)
				{
					T elementResult = static_cast<T>(0.0);
					// going through each element of leftM row
					for (int k = 0; k < l_numCols; k++)
					{
						int leftMLinearIndex = (i * l_numCols) + k; // (row * numCols) + col
						int rightMLinearIndex = (k * r_numCols) + j; // (row * numCols) + col
						elementResult += (leftM.m_matrixData[leftLinearIndex] * rightM.m_matrixData[rightLinearIndex]); // sum of r and c
					}
					int resultIndex = (i * r_numCols) + j; // (row * numCols) + col
					tempResult[resultIndex] = elementResult;
				}
			}
			Matrix<T> result(l_numRows, r_numCols, tempResult);
			delete[] tempResult;
			return result;
		}
		else
		{
			Matrix<T> result(1, 1);
			return result;
		}
	}
} 