// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Consts.h"
#include <algorithm>

namespace licui
{
	namespace math
	{
		template<class Type> POINT<Type> RotatedRectangleSize(const POINT<Type> &size, const double angle);

#pragma region Implementation
		template<class Type> POINT<Type> RotatedRectangleSize(const POINT<Type> &size, const double angle)
		{
			if (angle == 0 || size.X <= 0 || size.Y <= 0)
				return size;
			MATRIX<double> m{ 3, 3 }, r{ 3, 3 }, t{ 3, 3 };
			r.RotateZ(-angle);
			t.Translate(-size.X * 0.5, -size.Y * 0.5);
			m = t * r;
			VECTOR<double> v1{ 3 }, v2{ 3 }, v3{ 3 }, v4{ 3 };
			v1 = { 0, 0, 1 };
			v2 = { (double)size.X, 0, 1 };
			v3 = { (double)size.X, (double)size.Y, 1 };
			v4 = { 0, (double)size.Y, 1 };
			v1 = v1 * m;
			v2 = v2 * m;
			v3 = v3 * m;
			v4 = v4 * m;
			POINT<Type> result;
			result.X = (Type)(std::max(std::max(v1[0], v2[0]), std::max(v3[0], v4[0])) - std::min(std::min(v1[0], v2[0]), std::min(v3[0], v4[0])));
			result.Y = (Type)(std::max(std::max(v1[1], v2[1]), std::max(v3[1], v4[1])) - std::min(std::min(v1[1], v2[1]), std::min(v3[1], v4[1])));
			return result;
		}
#pragma endregion
	}
}