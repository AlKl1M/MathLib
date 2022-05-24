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
	private:
		int m_Row, m_Col, m_Elements;
		T* m_matrixData;
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
}