// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Math\Rectangle.h"

namespace licui
{
	namespace graphics
	{
		enum BLOCK_POINT_LOCATION
		{
			bplOutside = 0,
			bplInside = 1,
			bplLeft = 2,
			bplTop = 3,
			bplRight = 4,
			bplBottom = 5
		};

		BLOCK_POINT_LOCATION ClassifyBlockPoint(const int width, const int height, const int x, const int y, const math::RECTANGLE<int> &border, const math::RECTANGLE<int> &radius);
		void ClassifyBlockPoint(const int width, const int height, const int x, const int y, const math::RECTANGLE<int> &border, const math::RECTANGLE<int> &radius, const int factor, double *locations);
		BLOCK_POINT_LOCATION ClassifyBlockPoint(const int width, const int height, const int x, const int y, const math::RECTANGLE<int> &radius);
		void ClassifyBlockPoint(const int width, const int height, const int x, const int y, const math::RECTANGLE<int> &radius, const int factor, double &inside, double &outside);
	}
}