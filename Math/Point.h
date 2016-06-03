// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

namespace licui
{
	namespace math
	{
		template<class Type> union POINT
		{
			struct
			{
				Type X;
				Type Y;
			};
			Type Data[2];

			inline POINT<Type> operator+(const POINT<Type> &other) const;
			inline POINT<Type> &operator+=(const POINT<Type> &other);
			inline bool operator==(const POINT<Type> &other) const;
			inline bool operator!=(const POINT<Type> &other) const;
			inline POINT<Type> operator*(const Type v) const;
			inline POINT<Type> &operator*=(const Type v);
			inline POINT<Type> operator/(const Type v) const;
			inline POINT<Type> &operator/=(const Type v);
			inline Type &operator[](const unsigned char index);
			inline const Type &operator[](const unsigned char index) const;
		};

		template<class Type> POINT<Type> POINT<Type>::operator+(const POINT<Type> &other) const
		{
			return POINT<Type>{ X + other.X, Y + other.Y };
		}

		template<class Type> POINT<Type> &POINT<Type>::operator+=(const POINT<Type> &other)
		{
			X += other.X;
			Y += other.Y;
			return *this;
		}

		template<class Type> bool POINT<Type>::operator==(const POINT<Type> &other) const
		{
			return X == other.X && Y == other.Y;
		}

		template<class Type> bool POINT<Type>::operator!=(const POINT<Type> &other) const
		{
			return X != other.X || Y != other.Y;
		}

		template<class Type> POINT<Type> POINT<Type>::operator*(const Type v) const
		{
			return POINT<Type>{X * v, Y * v};
		}

		template<class Type> POINT<Type> &POINT<Type>::operator*=(const Type v)
		{
			X *= v;
			Y *= v;
			return *this;
		}

		template<class Type> POINT<Type> POINT<Type>::operator/(const Type v) const
		{
			return POINT<Type>{X / v, Y / v};
		}

		template<class Type> POINT<Type> &POINT<Type>::operator/=(const Type v)
		{
			X /= v;
			Y /= v;
			return *this;
		}

		template<class Type> Type &POINT<Type>::operator[](const unsigned char index)
		{
	#ifdef _DEBUG
			if (index > 1)
				throw "Index out of bounds";
	#endif
			return Data[index];
		}

		template<class Type> const Type &POINT<Type>::operator[](const unsigned char index) const
		{
	#ifdef _DEBUG
			if (index > 1)
				throw "Index out of bounds";
	#endif
			return Data[index];
		}
	}
}