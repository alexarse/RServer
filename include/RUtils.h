#include <iostream>
#include "axUtils.h"

namespace R
{
	template<typename T>
	struct Size2D_T
	{
		Size2D_T(const T& nrow = 0, const T& ncol = 0):
		row(nrow), col(ncol)
		{

		}

		T row, col;
	};

	typedef Size2D_T<unsigned int> Size2D;

	template <typename T>
	class Matrix2D
	{
	public:
		Matrix2D(T* data, const Size2D& size):
		_data(data),
		_size(size)
		{

		}

		void PrintSize() const
		{
			ax::Print("Matrix2D size :", _size.row, _size.col);
		}

		inline T& operator () (const unsigned int& row, const unsigned int& col)
		{
			unsigned int index = row + col * _size.row;
			return _data[index];
		}

		inline T& operator () (const unsigned int& index)
		{
			return _data[index];
		}

		void AssignValue(const unsigned int& row, const unsigned int& col, const T& value)
		{
			unsigned int index = row + col * _size.row;
			_data[index] = value;
		}

		T* GetData()
		{
			return _data;
		}

	private:
		T* _data;
		Size2D _size;
	};
}
