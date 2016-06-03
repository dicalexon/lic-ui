// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "Vector.h"
#ifdef _DEBUG
	#include <iostream>
#endif


namespace licui
{
	namespace math
	{
		template<class Type> struct MATRIX
		{
		public:
			struct MATRIX_COLUMN
			{
				friend MATRIX;
			protected:
				Type *m_pData;
	#ifdef _DEBUG
				size_t m_iHeight;
	#endif
			public:
				inline Type &operator[](const size_t y);
				inline const Type &operator[](const size_t y) const;
			};
		protected:
			size_t m_iWidth;
			size_t m_iHeight;
			Type *m_pData;
			MATRIX_COLUMN *m_pColumns;
		public:
			inline size_t getWidth() const;
			inline size_t getHeight() const;

			void setSize(const size_t width, const size_t height);

			inline MATRIX();
			inline MATRIX(const size_t width, const size_t height);
			MATRIX(const size_t width, const size_t height, const Type value);
			MATRIX(const MATRIX<Type> &other);
			inline MATRIX(MATRIX<Type> &&other);
			inline ~MATRIX();

			inline MATRIX_COLUMN &operator[](const size_t x);
			inline const MATRIX_COLUMN &operator[](const size_t x) const;
			bool operator==(const MATRIX<Type> &other);
			bool operator!=(const MATRIX<Type> &other);
			MATRIX<Type> operator+(const MATRIX<Type> &other);
			MATRIX<Type> operator+=(const MATRIX<Type> &other);
			MATRIX<Type> operator-(const MATRIX<Type> &other);
			MATRIX<Type> operator-=(const MATRIX<Type> &other);
			MATRIX<Type> operator*(const Type value);
			VECTOR<Type> operator*(const VECTOR<Type> &other);
			MATRIX<Type> operator*(const MATRIX<Type> &other);
			MATRIX<Type> operator*=(const Type value);
			MATRIX<Type> operator/(const Type value);
			MATRIX<Type> operator/=(const Type value);
			MATRIX<Type> &operator=(const MATRIX<Type> &other);
			MATRIX<Type> &operator=(MATRIX<Type> &&other);
			void Transpose();
			MATRIX<Type> Minor(const size_t x, const size_t y);
			Type Determinant();
			void Inverse();
			void Identity();
			void Translate(const Type x, const Type y);
			void Translate(const Type x, const Type y, const Type z);
			void Scale(const Type x, const Type y);
			void Scale(const Type x, const Type y, const Type z);
			void RotateX(const Type angle);
			void RotateY(const Type angle);
			void RotateZ(const Type angle);
	#ifdef _DEBUG
			void Print();
	#endif
		};

		template<class Type> VECTOR<Type> operator*(const VECTOR<Type> &vector, const MATRIX<Type> &matrix)
		{
	#ifdef _DEBUG
			if (vector.getLength() != matrix.getHeight())
				throw "Vector and matrix have incompatible sizes";
	#endif
			size_t x, i;
			VECTOR<Type> result{ matrix.getWidth() };
			for (x = 0; x < matrix.getWidth(); x++)
			{
				result[x] = 0;
				for (i = 0; i < vector.getLength(); i++)
					result[x] += vector[i] * matrix[x][i];
			}
			return result;
		}

		template<class Type> Type &MATRIX<Type>::MATRIX_COLUMN::operator[](const size_t y)
		{
	#ifdef _DEBUG
			if (y >= m_iHeight)
				throw "y is out of bounds";
	#endif
			return m_pData[y];
		}

		template<class Type> const Type &MATRIX<Type>::MATRIX_COLUMN::operator[](const size_t y) const
		{
	#ifdef _DEBUG
			if (y >= m_iHeight)
				throw "y is out of bounds";
	#endif
			return m_pData[y];
		}

		template<class Type> size_t MATRIX<Type>::getWidth() const
		{
			return m_iWidth;
		}

		template<class Type> size_t MATRIX<Type>::getHeight() const
		{
			return m_iHeight;
		}

		template<class Type> void MATRIX<Type>::setSize(const size_t width, const size_t height)
		{
			if (width != m_iWidth || height != m_iHeight)
			{
				if (m_iWidth)
				{
					delete[] m_pData;
					delete[] m_pColumns;
					m_pData = nullptr;
					m_pColumns = nullptr;
				}
				if (width > 0 && height > 0)
				{
					m_iWidth = width;
					m_iHeight = height;
					m_pColumns = new MATRIX_COLUMN[m_iWidth];
					m_pData = new Type[m_iWidth * m_iHeight];
					for (size_t x = 0; x < m_iWidth; x++)
					{
						m_pColumns[x].m_pData = &m_pData[x * m_iHeight];
	#ifdef _DEBUG
						m_pColumns[x].m_iHeight = m_iHeight;
	#endif
					}
				}
				else
					m_iWidth = m_iHeight = 0;
			}
		}

		template<class Type> MATRIX<Type>::MATRIX() : m_iWidth{ 0 }, m_iHeight{ 0 }, m_pColumns{ nullptr }, m_pData{ nullptr }
		{

		}

		template<class Type> MATRIX<Type>::MATRIX(const size_t width, const size_t height) : m_iWidth{ 0 }, m_iHeight{ 0 }, m_pColumns{ nullptr }, m_pData{ nullptr }
		{
			setSize(width, height);
		}

		template<class Type> MATRIX<Type>::MATRIX(const size_t width, const size_t height, const Type value) : m_iWidth{ 0 }, m_iHeight{ 0 }, m_pColumns{ nullptr }, m_pData{ nullptr }
		{
			setSize(width, height);
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] = (x == y) ? value : 0;
		}

		template<class Type> MATRIX<Type>::MATRIX(const MATRIX<Type> &other) : m_iWidth{ 0 }, m_iHeight{ 0 }, m_pColumns{ nullptr }, m_pData{ nullptr }
		{
			setSize(other.m_iWidth, other.m_iHeight);
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] = other[x][y];
		}

		template<class Type> MATRIX<Type>::MATRIX(MATRIX<Type> &&other) : m_iWidth{ other.m_iWidth }, m_iHeight{ other.m_iHeight }, m_pColumns{ other.m_pColumns }, m_pData{ other.m_pData }
		{
			other.m_iWidth = other.m_iHeight = 0;
			other.m_pData = nullptr;
			other.m_pColumns = nullptr;
		}

		template<class Type> MATRIX<Type>::~MATRIX()
		{
			setSize(0, 0);
		}

		template<class Type> typename MATRIX<Type>::MATRIX_COLUMN &MATRIX<Type>::operator[](const size_t x)
		{
			return m_pColumns[x];
		}

		template<class Type> const typename MATRIX<Type>::MATRIX_COLUMN &MATRIX<Type>::operator[](const size_t x) const
		{
			return m_pColumns[x];
		}

		template<class Type> bool MATRIX<Type>::operator==(const MATRIX<Type> &other)
		{
			if (other.m_iWidth != m_iWidth || other.m_iHeight != m_iHeight)
				return false;
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					if ((*this)[x][y] != other[x][y])
						return false;
			return true;
		}

		template<class Type> bool MATRIX<Type>::operator!=(const MATRIX<Type> &other)
		{
			if (other.m_iWidth != m_iWidth || other.m_iHeight != m_iHeight)
				return true;
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					if ((*this)[x][y] != other[x][y])
						return true;
			return false;
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::operator+(const MATRIX<Type> &other)
		{
	#ifdef _DEBUG
			if (other.m_iWidth != m_iWidth)
				throw "Matrices have different widthes";
			if (other.m_iHeight != m_iHeight)
				throw "Matrices have different heights";
	#endif
			MATRIX<Type> result{ m_iWidth, m_iHeight };
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					result[x][y] = (*this)[x][y] + other[x][y];
			return result;
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::operator+=(const MATRIX<Type> &other)
		{
	#ifdef _DEBUG
			if (other.m_iWidth != m_iWidth)
				throw "Matrices have different widthes";
			if (other.m_iHeight != m_iHeight)
				throw "Matrices have different heights";
	#endif
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] += other[x][y];
			return *this;
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::operator-(const MATRIX<Type> &other)
		{
	#ifdef _DEBUG
			if (other.m_iWidth != m_iWidth)
				throw "Matrices have different widthes";
			if (other.m_iHeight != m_iHeight)
				throw "Matrices have different heights";
	#endif
			MATRIX<Type> result{ m_iWidth, m_iHeight };
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					result[x][y] = (*this)[x][y] - other[x][y];
			return result;
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::operator-=(const MATRIX<Type> &other)
		{
	#ifdef _DEBUG
			if (other.m_iWidth != m_iWidth)
				throw "Matrices have different widthes";
			if (other.m_iHeight != m_iHeight)
				throw "Matrices have different heights";
	#endif
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] -= other[x][y];
			return *this;
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::operator*(const Type value)
		{
			MATRIX<Type> result{ m_iWidth, m_iHeight };
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					result[x][y] = (*this)[x][y] * value;
			return result;
		}

		template<class Type> VECTOR<Type> MATRIX<Type>::operator*(const VECTOR<Type> &other)
		{
	#ifdef _DEBUG
			if (other.getLength() != m_iHeight)
				throw "Vector length expected to be equal to matrix height";
	#endif
			VECTOR<Type> result{ m_iWidth };
			size_t i, k;
				for (i = 0; i < m_iWidth; i++)
				{
					result[i] = 0;
					for (k = 0; k < m_iHeight; k++)
						result[i] += (*this)[i][k] * other[k];
				}

			return result;
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::operator*=(const Type value)
		{
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] *= value;
			return *this;
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::operator*(const MATRIX<Type> &other)
		{
	#ifdef _DEBUG
			if (other.m_iWidth != m_iHeight)
				throw "Other matrix width expected to be equal to current matrix height";
			if (other.m_iHeight != m_iWidth)
				throw "Other matrix height expected to be equal to current matrix width";
	#endif
			MATRIX<Type> result{ other.m_iWidth, m_iHeight };
			size_t i, j, k;
			for (j = 0; j < m_iHeight; j++)
				for (i = 0; i < other.m_iWidth; i++)
				{
					result[i][j] = 0;
					for (k = 0; k < other.m_iHeight; k++)
						result[i][j] += other[i][k] * (*this)[k][j];
				}
			return result;
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::operator/(const Type value)
		{
			MATRIX<Type> result{ m_iWidth, m_iHeight };
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					result[x][y] = (*this)[x][y] / value;
			return result;
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::operator/=(const Type value)
		{
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] /= value;
			return *this;
		}

		template<class Type> MATRIX<Type> &MATRIX<Type>::operator=(const MATRIX<Type> &other)
		{
			setSize(other.m_iWidth, other.m_iHeight);
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] = other[x][y];
			return *this;
		}

		template<class Type> MATRIX<Type> &MATRIX<Type>::operator=(MATRIX<Type> &&other)
		{
			if (this != &other)
			{
				setSize(0, 0);
				m_iWidth = other.m_iWidth;
				m_iHeight = other.m_iHeight;
				m_pColumns = other.m_pColumns;
				m_pData = other.m_pData;
				other.m_iWidth = other.m_iHeight = 0;
				other.m_pData = nullptr;
				other.m_pColumns = nullptr;
			}
			return *this;
		}

		template<class Type> void MATRIX<Type>::Transpose()
		{
			size_t x, y;
			Type t;
			for (x = 0; x < m_iWidth; x++)
				for (y = x + 1; y < m_iHeight; y++)
				{
					t = (*this)[x][y];
					(*this)[x][y] = (*this)[y][x];
					(*this)[y][x] = t;
				}
		}

		template<class Type> MATRIX<Type> MATRIX<Type>::Minor(const size_t x, const size_t y)
		{
	#ifdef _DEBUG
			if (m_iWidth <= 1 )
				throw "Matrix have too small width";
			if (m_iHeight <= 1)
				throw "Matrix have too small height";
			if (x >= m_iWidth)
				throw "x is out of bounds";
			if (y >= m_iHeight)
				throw "y is out of bounds";
	#endif
			MATRIX<Type> result{ m_iWidth - 1, m_iHeight - 1 };
			size_t tx, ty, i, j{ 0 };
			for (ty = 0; ty < m_iHeight; ty++)
				if (ty != y)
				{
					i = 0;
					for (tx = 0; tx < m_iWidth; tx++)
						if (tx != x)
							result[i++][j] = (*this)[tx][ty];
					j++;
				}
			return result;
		}

		template<class Type> Type MATRIX<Type>::Determinant()
		{
			switch (m_iWidth)
			{
			case 1:
				return (*this)[0][0];
			case 2:
				return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
			default:
				int j = 1;
				Type result{ 0 };
				for (size_t x = 0; x < m_iWidth; x++)
				{
					result += (*this)[x][0] * Minor(x, 0).Determinant() * j;
					j = -j;
				}
				return result;
			}
		}

		template<class Type> void MATRIX<Type>::Inverse()
		{
			MATRIX<Type> result{ m_iWidth, m_iHeight };
			size_t x, y;
			Type det = Determinant();
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					result[y][x] = Minor(x, y).Determinant() * ((x + y) % 2 == 0 ? 1 : -1) / det;
			(*this) = result;
		}

		template<class Type> void MATRIX<Type>::Identity()
		{
			size_t x, y;
			for (x = 0; x < m_iWidth; x++)
				for (y = 0; y < m_iHeight; y++)
					(*this)[x][y] = (x == y) ? (Type)1 : (Type)0;
		}

		template<class Type> void MATRIX<Type>::Translate(const Type x, const Type y)
		{
	#ifdef _DEBUG
			if (m_iWidth < 3)
				throw "Matrix have too small width";
			if (m_iHeight < 3)
				throw "Matrix have too small height";
	#endif
			(*this)[0][0] = 1; (*this)[1][0] = 0; (*this)[2][0] = 0;
			(*this)[0][1] = 0; (*this)[1][1] = 1; (*this)[2][1] = 0;
			(*this)[0][2] = x; (*this)[1][2] = y; (*this)[2][2] = 1;
		}

		template<class Type> void MATRIX<Type>::Translate(const Type x, const Type y, const Type z)
		{
	#ifdef _DEBUG
			if (m_iWidth < 4)
				throw "Matrix have too small width";
			if (m_iHeight < 4)
				throw "Matrix have too small height";
	#endif
			(*this)[0][0] = 1; (*this)[1][0] = 0; (*this)[2][0] = 0; (*this)[3][0] = 0;
			(*this)[0][1] = 0; (*this)[1][1] = 1; (*this)[2][1] = 0; (*this)[3][1] = 0;
			(*this)[0][2] = 0; (*this)[1][2] = 0; (*this)[2][2] = 1; (*this)[3][2] = 0;
			(*this)[0][3] = x; (*this)[1][3] = y; (*this)[2][3] = z; (*this)[3][3] = 1;
		}

		template<class Type> void MATRIX<Type>::Scale(const Type x, const Type y)
		{
	#ifdef _DEBUG
			if (m_iWidth < 3)
				throw "Matrix have too small width";
			if (m_iHeight < 3)
				throw "Matrix have too small height";
	#endif
			(*this)[0][0] = x; (*this)[1][0] = 0; (*this)[2][0] = 0;
			(*this)[0][1] = 0; (*this)[1][1] = y; (*this)[2][1] = 0;
			(*this)[0][2] = 0; (*this)[1][2] = 0; (*this)[2][2] = 1;
		}

		template<class Type> void MATRIX<Type>::Scale(const Type x, const Type y, const Type z)
		{
	#ifdef _DEBUG
			if (m_iWidth < 4)
				throw "Matrix have too small width";
			if (m_iHeight < 4)
				throw "Matrix have too small height";
	#endif
			(*this)[0][0] = x; (*this)[1][0] = 0; (*this)[2][0] = 0; (*this)[3][0] = 0;
			(*this)[0][1] = 0; (*this)[1][1] = y; (*this)[2][1] = 0; (*this)[3][1] = 0;
			(*this)[0][2] = 0; (*this)[1][2] = 0; (*this)[2][2] = z; (*this)[3][2] = 0;
			(*this)[0][3] = 0; (*this)[1][3] = 0; (*this)[2][3] = 0; (*this)[3][3] = 1;
		}

		template<class Type> void MATRIX<Type>::RotateX(const Type angle)
		{
	#ifdef _DEBUG
			if (m_iWidth < 4)
				throw "Matrix have too small width";
			if (m_iHeight < 4)
				throw "Matrix have too small height";
	#endif
			Type sin{ std::sin(angle) }, cos{ std::cos(angle) };
			(*this)[0][0] = 1;		(*this)[1][0] = 0;		(*this)[2][0] = 0;		(*this)[3][0] = 0;
			(*this)[0][1] = 0;		(*this)[1][1] = cos;	(*this)[2][1] = sin;	(*this)[3][1] = 0;
			(*this)[0][2] = 0;		(*this)[1][2] = -sin;	(*this)[2][2] = cos;	(*this)[3][2] = 0;
			(*this)[0][3] = 0;		(*this)[1][3] = 0;		(*this)[2][3] = 0;		(*this)[3][3] = 1;
		}

		template<class Type> void MATRIX<Type>::RotateY(const Type angle)
		{
	#ifdef _DEBUG
			if (m_iWidth < 4)
				throw "Matrix have too small width";
			if (m_iHeight < 4)
				throw "Matrix have too small height";
	#endif
			Type sin{ std::sin(angle) }, cos{ std::cos(angle) };
			(*this)[0][0] = cos;	(*this)[1][0] = 0;		(*this)[2][0] = -sin;	(*this)[3][0] = 0;
			(*this)[0][1] = 0;		(*this)[1][1] = 1;		(*this)[2][1] = 0;		(*this)[3][1] = 0;
			(*this)[0][2] = sin;	(*this)[1][2] = 0;		(*this)[2][2] = cos;	(*this)[3][2] = 0;
			(*this)[0][3] = 0;		(*this)[1][3] = 0;		(*this)[2][3] = 0;		(*this)[3][3] = 1;
		}

		template<class Type> void MATRIX<Type>::RotateZ(const Type angle)
		{
	#ifdef _DEBUG
			if (m_iWidth < 3)
				throw "Matrix have too small width";
			if (m_iHeight < 3)
				throw "Matrix have too small height";
	#endif
			Identity(); // Use Identity() instead of direct element assignement to cover both 3- and 4- dimentional matrices
			Type sin{ std::sin(angle) }, cos{ std::cos(angle) };
			(*this)[0][0] = cos;	(*this)[1][0] = sin;
			(*this)[0][1] = -sin;	(*this)[1][1] = cos;
		}

	#ifdef _DEBUG
		template<class Type> void MATRIX<Type>::Print()
		{
			for (size_t y = 0; y < m_iHeight; y++)
			{
				for (size_t x = 0; x < m_iWidth; x++)
				{
					printf("%.3f", (*this)[x][y]);
					std::cout << " ";
				}
				std::cout << std::endl;
			}
		}
	#endif
	}
}