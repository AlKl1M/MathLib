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

		bool operator== (const Matrix<T>& rightM);
		Matrix<T> FindSubMatrix(int Row, int Col);
		T Determinant();
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
			return (m_matrixData[0] * m_matrixData[3]) - (m_matrixData[1] * m_matrixData[2]);
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
	
} 