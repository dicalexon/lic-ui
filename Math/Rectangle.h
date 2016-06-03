// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include <algorithm>
#include "Point.h"

namespace licui
{
	namespace math
	{
		template<class Type> union RECTANGLE
		{
			struct
			{
				Type Left;
				Type Top;
				Type Right;
				Type Bottom;
			};
		
			Type Data[4];

			inline Type Width() const;
			inline Type Height() const;
			inline POINT<Type> LeftTop() const;
			inline POINT<Type> RightBottom() const;
			inline Type Area() const;
			inline bool IsInversed() const;
			inline bool IsValid() const;
			inline bool IsEmpty() const;

			inline RECTANGLE<Type> operator+(const RECTANGLE<Type> &other) const;
			RECTANGLE<Type> &operator+=(const RECTANGLE<Type> &other);
			inline bool operator==(const RECTANGLE<Type> &other) const;
			inline bool operator!=(const RECTANGLE<Type> &other) const;
			inline Type &operator[](const unsigned char index);
			inline const Type &operator[](const unsigned char index) const;

			inline bool HasIntersection(const RECTANGLE<Type> &other) const;
			RECTANGLE<Type> Intersection(const RECTANGLE<Type> &other) const;
			inline RECTANGLE<Type> operator*(const RECTANGLE<Type> &other) const;
			RECTANGLE<Type> &operator*=(const RECTANGLE<Type> &other);
		};

		template<class Type> Type RECTANGLE<Type>::Width() const
		{
			return Right - Left;
		}

		template<class Type> Type RECTANGLE<Type>::Height() const
		{
			return Bottom - Top;
		}

		template<class Type> POINT<Type> RECTANGLE<Type>::LeftTop() const
		{
			return POINT<Type>{Left, Top};
		}

		template<class Type> POINT<Type> RECTANGLE<Type>::RightBottom() const
		{
			return POINT<Type>{Right, Bottom};
		}

		template<class Type> Type RECTANGLE<Type>::Area() const
		{
			return (Right - Left) * (Bottom - Top);
		}

		template<class Type> bool RECTANGLE<Type>::IsInversed() const
		{
			return Right < Left && Bottom < Top;
		}

		template<class Type> bool RECTANGLE<Type>::IsValid() const
		{
			return Right >= Left && Bottom >= Top;
		}

		template<class Type> bool RECTANGLE<Type>::IsEmpty() const
		{
			return Right == Left && Bottom == Top;
		}

		template<class Type> RECTANGLE<Type> RECTANGLE<Type>::operator+(const RECTANGLE<Type> &other) const
		{
			return RECTANGLE<Type>{std::min(Left, other.Left), std::min(Top, other.Top), std::max(Right, other.Right), std::max(Bottom, other.Bottom)};
		}

		template<class Type> RECTANGLE<Type> &RECTANGLE<Type>::operator+=(const RECTANGLE<Type> &other)
		{
			Left = std::min(Left, other.Left);
			Top = std::min(Top, other.Top);
			Right = std::max(Right, other.Right);
			Bottom = std::max(Bottom, other.Bottom);
			return *this;
		}

		template<class Type> bool RECTANGLE<Type>::operator==(const RECTANGLE<Type> &other) const
		{
			return Left == other.Left && Top == other.Top && Right == other.Right && Bottom == other.Bottom;
		}

		template<class Type> bool RECTANGLE<Type>::operator!=(const RECTANGLE<Type> &other) const
		{
			return Left != other.Left || Top != other.Top || Right != other.Right || Bottom != other.Bottom;
		}

		template<class Type> Type &RECTANGLE<Type>::operator[](const unsigned char index)
		{
	#ifdef _DEBUG
			if (index > 3)
				throw "Index out of bounds";
	#endif
			return Data[index];
		}

		template<class Type> const Type &RECTANGLE<Type>::operator[](const unsigned char index) const
		{
	#ifdef _DEBUG
			if (index > 3)
				throw "Index out of bounds";
	#endif
			return Data[index];
		}

		template<class Type> bool RECTANGLE<Type>::HasIntersection(const RECTANGLE<Type> &other) const
		{
			return other.Top < Bottom && other.Bottom > Top && other.Left < Right && other.Right > Left;
		}

		template<class Type> RECTANGLE<Type> RECTANGLE<Type>::Intersection(const RECTANGLE<Type> &other) const
		{
			RECTANGLE<Type> result{ std::max(Left, other.Left), std::max(Top, other.Top), std::min(Right, other.Right), std::min(Bottom, other.Bottom) };
			if (result.Right <= result.Left || result.Bottom <= result.Top)
				return RECTANGLE<Type>{0, 0, 0, 0};
			return result;
		}

		template<class Type> RECTANGLE<Type> RECTANGLE<Type>::operator*(const RECTANGLE<Type> &other) const
		{
			return Intersection(other);
		}

		template<class Type> RECTANGLE<Type> &RECTANGLE<Type>::operator*=(const RECTANGLE<Type> &other)
		{
			Left = std::max(Left, other.Left);
			Top = std::max(Top, other.Top);
			Right = std::min(Right, other.Right);
			Bottom = std::min(Bottom, other.Bottom);
			if (Right <= Left || Bottom <= Top)
				Left = Top = Right = Bottom = 0;
			return *this;
		}
	}
}