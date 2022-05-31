#pragma once

namespace mt {

	template <class T>
	class Vector {
	public:
		Vector();
		Vector(Dim);
		Vector(std::vector<T> data);
		~Vector();

		int getNumDims() const;
		void GetElement(int index) const;
		void SetElement(int index, T value);

		Vector<T> operator+ (const Vector<T>& vector) const;
		Vector<T> operator- (const Vector<T>& vector) const;
		Vector<T> operator* (const T& element) const;

	private:
		std::vector<T> m_vectorData;
		int m_Dim;
	};
}
