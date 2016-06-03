// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

namespace licui
{
	namespace math
	{
		template<class Type> struct VECTOR
		{
		protected:
			size_t m_iLength;
			Type *m_pData;
		public:
			inline size_t getLength() const;

			void setLength(const size_t length);

			inline VECTOR();
			inline VECTOR(const size_t length);
			VECTOR(const size_t length, const Type value);
			inline VECTOR(const Type x, const Type y, const Type z);
			inline VECTOR(const Type x, const Type y, const Type z, const Type w);
			VECTOR(const VECTOR<Type> &other);
			inline VECTOR(VECTOR<Type> &&other);
			inline ~VECTOR();

			inline Type &operator[](const size_t index);
			inline const Type &operator[](const size_t index) const;
			bool operator==(const VECTOR<Type> &other) const;
			bool operator!=(const VECTOR<Type> &other) const;
			inline Type operator*(const VECTOR<Type> &other) const;
			inline VECTOR<Type> operator*(const Type value) const;
			inline VECTOR<Type> operator*=(const Type value);
			inline VECTOR<Type> operator/(const Type value) const;
			inline VECTOR<Type> operator/=(const Type value);
			inline VECTOR<Type> operator+(const VECTOR<Type> &other) const;
			inline VECTOR<Type> operator+=(const VECTOR<Type> &other);
			inline VECTOR<Type> operator-(const VECTOR<Type> &other) const;
			inline VECTOR<Type> operator-=(const VECTOR<Type> &other);
			inline VECTOR<Type> operator^(const VECTOR<Type> &other) const;
			VECTOR<Type> operator^=(const VECTOR<Type> &other);
			VECTOR<Type> &operator=(const VECTOR<Type> &other);
			VECTOR<Type> &operator=(VECTOR<Type> &&other);

			inline Type Norma() const;
			inline void Inverse();
		};

		template<class Type> size_t VECTOR<Type>::getLength() const
		{
			return m_iLength;
		}

		template<class Type> void VECTOR<Type>::setLength(const size_t length)
		{
			if (length != m_iLength)
			{
				if (m_iLength > 0)
				{
					delete[] m_pData;
					m_pData = nullptr;
				}
				m_iLength = length;
				if (m_iLength > 0)
					m_pData = new Type[m_iLength];
			}
		}

		template<class Type> VECTOR<Type>::VECTOR() : m_iLength{ 0 }, m_pData{ nullptr }
		{

		}

		template<class Type> VECTOR<Type>::VECTOR(const size_t length) : m_iLength{ length }, m_pData{ nullptr }
		{
			if (m_iLength > 0)
				m_pData = new Type[m_iLength];
		}

		template<class Type> VECTOR<Type>::VECTOR(const size_t length, const Type value) : m_iLength{ length }, m_pData{ nullptr }
		{
			if (m_iLength > 0)
			{
				m_pData = new Type[m_iLength];
				for (size_t index = 0; index < m_iLength; index++)
					m_pData[index] = value;
			}
		}

		template<class Type> VECTOR<Type>::VECTOR(const Type x, const Type y, const Type z) : m_iLength{ 3 }
		{
			m_pData = new Type[m_iLength];
			m_pData[0] = x;
			m_pData[1] = y;
			m_pData[2] = z;
		}

		template<class Type> VECTOR<Type>::VECTOR(const Type x, const Type y, const Type z, const Type w) : m_iLength{ 4 }
		{
			m_pData = new Type[m_iLength];
			m_pData[0] = x;
			m_pData[1] = y;
			m_pData[2] = z;
			m_pData[3] = w;
		}

		template<class Type> VECTOR<Type>::VECTOR(const VECTOR<Type> &other) :m_iLength{ other.m_iLength }, m_pData{ nullptr }
		{
			if (m_iLength > 0)
			{
				m_pData = new Type[m_iLength];
				for (size_t i = 0; i < m_iLength; i++)
					m_pData[i] = other.m_pData[i];
			}
		}

		template<class Type> VECTOR<Type>::VECTOR(VECTOR<Type> &&other) : m_iLength{ other.m_iLength }, m_pData{ other.m_pData }
		{
			other.m_iLength = 0;
			other.m_pData = nullptr;
		}

		template<class Type> VECTOR<Type>::~VECTOR()
		{
			if (m_iLength > 0)
				delete[] m_pData;
		}

		template<class Type> Type &VECTOR<Type>::operator[](const size_t index)
		{
		#ifdef _DEBUG
			if (index >= m_iLength)
				throw "index out of bounds";
		#endif
			return m_pData[index];
		}

		template<class Type> const Type &VECTOR<Type>::operator[](const size_t index) const
		{
		#ifdef _DEBUG
			if (index >= m_iLength)
				throw "index out of bounds";
		#endif
			return m_pData[index];
		}

		template<class Type> bool VECTOR<Type>::operator==(const VECTOR<Type> &other) const
		{
			if (other.m_iLength != m_iLength)
				return false;
			for (size_t index = 0; index < m_iLength; index++)
				if (m_pData[index] != other.m_pData[index])
					return false;
			return true;
		}

		template<class Type> bool VECTOR<Type>::operator!=(const VECTOR<Type> &other) const
		{
			if (other.m_iLength != m_iLength)
				return true;
			for (size_t index = 0; index < m_iLength; index++)
				if (m_pData[index] != other.m_pData[index])
					return true;
			return false;
		}

		template<class Type> Type VECTOR<Type>::operator*(const VECTOR<Type> &other) const
		{
		#ifdef _DEBUG
			if (other.m_iLength != m_iLength)
				throw "Vectors have different lengthes";
		#endif
			Type result{ 0 };
			for (size_t index = 0; index < m_iLength; index++)
				result += m_pData[index] * other.m_pData[index];
			return result;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator*(const Type value) const
		{
			VECTOR<Type> result{ m_iLength };
			for (size_t index = 0; index < m_iLength; index++)
				result.m_pData[index] = m_pData[index] * value;
			return result;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator*=(const Type value)
		{
			for (size_t index = 0; index < m_iLength; index++)
				m_pData[index] *= value;
			return *this;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator/(const Type value) const
		{
			VECTOR<Type> result{ m_iLength };
			for (size_t index = 0; index < m_iLength; index++)
				result.m_pData[index] = m_pData[index] / value;
			return result;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator/=(const Type value)
		{
			for (size_t index = 0; index < m_iLength; index++)
				m_pData[index] /= value;
			return *this;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator+(const VECTOR<Type> &other) const
		{
		#ifdef _DEBUG
			if (other.m_iLength != m_iLength)
				throw "Vectors have different lengthes";
		#endif
			VECTOR<Type> result{ m_iLength };
			for (size_t index = 0; index < m_iLength; index++)
				result.m_pData[index] = m_pData[index] + other.m_pData[index];
			return result;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator+=(const VECTOR<Type> &other)
		{
		#ifdef _DEBUG
			if (other.m_iLength != m_iLength)
				throw "Vectors have different lengthes";
		#endif
			for (size_t index = 0; index < m_iLength; index++)
				m_pData[index] += other.m_pData[index];
			return *this;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator-(const VECTOR<Type> &other) const
		{
		#ifdef _DEBUG
			if (other.m_iLength != m_iLength)
				throw "Vectors have different lengthes";
		#endif
			VECTOR<Type> result{ m_iLength };
			for (size_t index = 0; index < m_iLength; index++)
				result.m_pData[index] = m_pData[index] - other.m_pData[index];
			return result;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator-=(const VECTOR<Type> &other)
		{
		#ifdef _DEBUG
			if (other.m_iLength != m_iLength)
				throw "Vectors have different lengthes";
		#endif
			for (size_t index = 0; index < m_iLength; index++)
				m_pData[index] -= other.m_pData[index];
			return *this;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator^(const VECTOR<Type> &other) const
		{
		#ifdef _DEBUG
			if (other.m_iLength != m_iLength)
				throw "Vectors have different lengthes";
			if (m_iLength != 3)
				throw "Vectors length expected to be 3";
		#endif
			VECTOR<Type> result{ 3 };
			result.m_pData[0] = m_pData[1] * other.m_pData[2] - m_pData[2] * other.m_pData[1];
			result.m_pData[1] = m_pData[2] * other.m_pData[0] - m_pData[0] * other.m_pData[2];
			result.m_pData[2] = m_pData[0] * other.m_pData[1] - m_pData[1] - other.m_pData[0];
			return result;
		}

		template<class Type> VECTOR<Type> VECTOR<Type>::operator^=(const VECTOR<Type> &other)
		{
		#ifdef _DEBUG
			if (other.m_iLength != m_iLength)
				throw "Vectors have different lengthes";
			if (m_iLength != 3)
				throw "Vectors length expected to be 3";
		#endif
			VECTOR<Type> result{ 3 };
			result.m_pData[0] = m_pData[1] * other.m_pData[2] - m_pData[2] * other.m_pData[1];
			result.m_pData[1] = m_pData[2] * other.m_pData[0] - m_pData[0] * other.m_pData[2];
			result.m_pData[2] = m_pData[0] * other.m_pData[1] - m_pData[1] - other.m_pData[0];
			m_pData[0] = result.m_pData[0];
			m_pData[1] = result.m_pData[1];
			m_pData[2] = result.m_pData[2];
			return result;
		}

		template<class Type> VECTOR<Type> &VECTOR<Type>::operator=(const VECTOR<Type> &other)
		{
			setLength(other.m_iLength);
			for (size_t index = 0; index < m_iLength; index++)
				m_pData[index] = other.m_pData[index];
			return *this;
		}

		template<class Type> VECTOR<Type> &VECTOR<Type>::operator=(VECTOR<Type> &&other)
		{
			if (this != &other)
			{
				if (m_iLength > 0)
					delete[] m_pData;
				m_iLength = other.m_iLength;
				m_pData = other.m_pData;
				other.m_iLength = 0;
				other.m_pData = nullptr;
			}
			return *this;
		}

		template<class Type> Type VECTOR<Type>::Norma() const
		{
			Type result{ 0 };
			for (size_t index = 0; index < m_iLength; index++)
				result += m_pData[index] * m_pData[index];
			return result;
		}

		template<class Type> void VECTOR<Type>::Inverse()
		{
			for (size_t index = 0; index < m_iLength; index++)
				m_pData[index] = -m_pData[index];
		}
	}
}