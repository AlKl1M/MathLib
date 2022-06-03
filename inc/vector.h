#pragma once
#include <vector>
#include <stdexcept>
#include "inc/matrix.h"

namespace mt {

	template <class T>
	class Vector {
	public:
		Vector();
		Vector(int Dim);
		Vector(std::vector<T> data);
		~Vector();

		int getNumDims() const;
		T GetElement(int index) const;
		void SetElement(int index, T value);

		Vector<T> operator+ (const Vector<T>& v) const;
		Vector<T> operator- (const Vector<T>& v) const;
		Vector<T> operator* (const T& element) const;

		template <class T> friend std::ostream& operator<< (std::ostream& out, const Vector<T>& vector);

	private:
		int m_Dim;
		std::vector<T> m_vectorData;
	};

	 template <class T>
	 Vector<T>::Vector()
	 {
		 m_Dim = 0;
		 m_vectorData = std::vector<T>();
	 }

	 template <class T>
	 Vector<T>::Vector(int n_D)
	 {
		 m_Dim = n_D;
		 m_vectorData = std::vector<T>(n_D, static_cast<T>(0.0));
	 }

	 template <class T>
	 Vector<T>::Vector(std::vector<T> data)
	 {
		 m_Dim = data.size();
		 m_vectorData = data;
	 }

	 template <class T>
	 Vector<T>::~Vector()
	 {

	 }

	 template <class T>
	 int Vector<T>::getNumDims() const
	 {
		 return m_Dim;
	 }

	 template <class T>
	 T Vector<T>::GetElement(int index) const
	 {
		 return m_vectorData[index];
	 }

	 template <class T>
	 void Vector<T>::SetElement(int index, T value)
	 {
		 m_vectorData[index] = value;
	 }

	 template <class T>
	 Vector<T> Vector<T>::operator+ (const Vector<T>& v) const
	 {
		 if (m_Dim != v.m_Dim)
			 throw std::invalid_argument("Vectors dims are different");

		 std::vector<T> resultV;
		 for (int i = 0; i < m_Dim; i++)
			 resultV.push_back(m_vectorData.at(i) + v.m_vectorData.at(i));
		 Vector<T> result(resultV);
		 return result;
	 }

	 template <class T>
	 Vector<T> Vector<T>::operator- (const Vector<T>& v) const
	 {
		 if (m_Dim != v.m_Dim)
			 throw std::invalid_argument("Vectors dims are different");

		 std::vector<T> resultV;
		 for (int i = 0; i < m_Dim; i++)
			 resultV.push_back(m_vectorData.at(i) - v.m_vectorData.at(i));

		 Vector<T> result(resultV);
		 return result;
	 }

	 template <class T>
	 Vector<T> Vector<T>::operator* (const T& element) const
	 {
		 std::vector<T> resultV;
		 for (int i = 0; i < m_Dim; i++)
			 resultV.push_back(m_vectorData.at(i) * element);
		 Vector<T> result(resultV);
		 return resultV;
	 }

	 template <class T>
	 std::ostream& operator<< (std::ostream& out, const Vector<T>& vector)
	 {
		 for (int i = 0; i < vector.m_Dim; i++)
			 out << vector.m_vectorData[i] << " ";
		 return out;
	 }

}
