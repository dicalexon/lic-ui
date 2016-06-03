// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "ClassifyPoint.h"
#include <algorithm>

namespace licui
{
	namespace graphics
	{
		/**
		@par Idea and formulas:
		- For outer and inner corner checks bezier n^2 curves are used(P - internal radius bezier points, R - external radius bezier points):
		- Left-top corner: R1(0, radius[0]), R2(0, 0), R3(radius[0], 0), P1(border[0], radius[0]), P2(border[0], border[1]), P3(radius[0], border[1])
		- Right-top corner: R1(width, radius[1]), R2(width, 0), R3(width - radius[1], 0), P1(width - border[2], radius[1]), P2(width - border[2], border[1]), P3(width - radius[1], border[1])
		- Left-bottom corner: R1(0, height - radius[3]), R2(0, height), R3(radius[3], height), P1(border[0], height - radius[3]), P2(border[0], height - border[3]), P3(radius[3], height - border[3])
		- Right-bottom corner: R1(width, height - radius[2]), R2(width, height), R3(width - radius[2], height), P1(width - border[2], height - radius[2]), P2(width - border[2], height - border[3]), P3(width - radius[2], height - border[3])
		- P = (1 - t) * (1 - t) * P1 + 2 * (1 - t) * t * P2 + t * t * P3 - Bezier curve
		- D = b * b - 4 * a * c - Discriminant
		- x = ( - b +- SQRT(D))/ (2 * a)
		- First search t by known x: Final formula(assuming x2 = x1 due to selected points) is t = SQRT((x - x1) / (x3 - x1))
		- Than search curve y: Final formula is y = (1 - t) ^ 2 * y1 + 2 * (1 - t) * t * y2 + t ^ 2 * y3
		- Finaly compare found y with current point y and deside where point is
		*/
		BLOCK_POINT_LOCATION ClassifyBlockPoint(const int width, const int height, const int x, const int y, const math::RECTANGLE<int> &border, const math::RECTANGLE<int> &radius)
		{
#ifdef _DEBUG
			if (width < 0)
				throw "width is invalid";
			if (height < 0)
				throw "height is invalid";
			if (border[0] < 0)
				throw "border[0] is invalid";
			if (border[1] < 0)
				throw "border[1] is invalid";
			if (border[2] < 0)
				throw "border[2] is invalid";
			if (border[3] < 0)
				throw "border[3] is invalid";
			if (radius[0] < 0)
				throw "radius[0] is invalid";
			if (radius[1] < 0)
				throw "radius[1] is invalid";
			if (radius[2] < 0)
				throw "radius[2] is invalid";
			if (radius[3] < 0)
				throw "radius[3] is invalid";
#endif
			// Check point is completely outside of block
			if (x < 0 || y < 0 || x >= width || y >= height)
				return bplOutside;
			// Process left border
			if (x < std::max(std::max(radius[0], radius[3]), border[0])) // Check point is in border & corners zone
				if (border[1] == 0 || y >= x * border[1] / border[0]) // Check point does not belongs to top border
					if (border[3] == 0 || y <= height - x * border[3] / border[0]) // Check point does not belongs to bottom border
					{
						if (radius[0] > 0 && y < radius[0] && x < radius[0]) // Check point is out of lect-top corner radius
						{
							double t = std::sqrt(x / (double)radius[0]);
							double ty = std::pow(1 - t, 2) * radius[0];
							if (y <= ty)
								return bplOutside;
						}
						if (radius[3] > 0 && y >= height - radius[3] && x < radius[3]) // Check point is out of left-bottom corner radius
						{
							double t = std::sqrt(x / (double)radius[3]);
							double ty = std::pow(1 - t, 2) * (height - 1 - radius[3]) + 2 * (1 - t) * t * (height - 1) + std::pow(t, 2) * (height - 1);
							if (y >= ty)
								return bplOutside;
						}
						if (x < border[0] || y < border[1] || y > height - border[3]) // Point is completely inside border
							return bplLeft;
						if (radius[0] > border[0] && y < radius[0] && x < radius[0]) // Check point is in left-top corner
						{
							double t = std::sqrt((x - border[0]) / (radius[0] - (double)border[0]));
							double ty = std::pow(1 - t, 2) * radius[0] + 2 * (1 - t) * t * border[1] + std::pow(t, 2) * border[1];
							if (y < ty)
								return bplLeft;
						}
						if (radius[3] > border[0] && y >= height - radius[3] && x < radius[3]) // Check point is in left-bottom corner
						{
							double t = std::sqrt((x - border[0]) / (radius[3] - (double)border[0]));
							double ty = std::pow(1 - t, 2) * (height - 1 - radius[3]) + 2 * (1 - t) * t * (height - 1 - border[3]) + std::pow(t, 2) * (height - 1 - border[3]);
							if (y > ty)
								return bplLeft;
						}
					}
			// Process right border
			if (x >= width - std::max(std::max(radius[1], radius[2]), border[2])) // Check point is in border & corners zone
				if (border[1] == 0 || y >= (width - x) * border[1] / border[2]) // Check point does not belongs to top border
					if (border[3] == 0 || y <= height - (width - x) * border[3] / border[2]) // Check point does not belongs to bottom border
					{
						if (radius[1] > 0 && y < radius[1] && x >= width - radius[1]) // Check point is out of right-top corner radius
						{
							double t = std::sqrt((width - 1 - x) / (double)radius[1]);
							double ty = std::pow(1 - t, 2) * radius[1];
							if (y <= ty)
								return bplOutside;
						}
						if (radius[2] > 0 && y >= height - radius[2] && x > width - radius[2]) // Check point is out of right-bottom radius
						{
							double t = std::sqrt((width - 1 - x) / (double)radius[2]);
							double ty = std::pow(1 - t, 2) * (height - 1 - radius[2]) + 2 * (1 - t) * t * (height - 1) + std::pow(t, 2) * (height - 1);
							if (y >= ty)
								return bplOutside;
						}
						if (x >= width - border[2] || y < border[1] || y >= height - border[3]) // Point is completely inside border
							return bplRight;
						if (radius[1] > border[2] && y < radius[1] && x >= width - radius[1]) // Check point is in right-top corner
						{
							double t = std::sqrt((x - (width - 1) + border[2]) / ((double)border[2] - radius[1]));
							double ty = std::pow(1 - t, 2) * radius[1] + 2 * (1 - t) * t * border[1] + std::pow(t, 2) * border[1];
							if (y < ty)
								return bplRight;
						}
						if (radius[2] > border[2] && y >= height - radius[2] && x >= width - radius[2]) // Check point is in right-bottom corner
						{
							double t = std::sqrt((x - (width - 1) + border[2]) / ((double)border[2] - radius[2]));
							double ty = std::pow(1 - t, 2) * (height - 1 - radius[2]) + 2 * (1 - t) * t * (height - 1 - border[3]) + std::pow(t, 2) * (height - 1 - border[3]);
							if (y > ty)
								return bplRight;
						}
					}
			// Process top border
			if (y < std::max(std::max(radius[0], radius[1]), border[1])) // Check point is in border & corners zone
				if (border[0] == 0 || y < x * border[1] / border[0]) // Check point does not belongs to left border
					if (border[2] == 0 || y < (width - x) * border[1] / border[2]) // Check point does not belongs to right border
					{
						if (radius[0] > 0 && x < radius[0] && y < radius[0]) // Check point is out of left-top corner radius
						{
							double t = std::sqrt(x / (double)radius[0]);
							double ty = std::pow(1 - t, 2) * radius[0];
							if (y < ty)
								return bplOutside;
						}
						if (radius[1] > 0 && x >= width - radius[1] && y < radius[1]) // Check point is out of right-top corner radius
						{
							double t = std::sqrt((width - 1 - x) / (double)radius[1]);
							double ty = std::pow(1 - t, 2) * radius[1];
							if (y < ty)
								return bplOutside;
						}
						if (y < border[1] || x < border[0] || x > width - border[2]) // Point is completely inside border
							return bplTop;
						if (radius[0] > border[1] && x < radius[0] && y < radius[0]) // Check point is in left-top corner
						{
							double t = std::sqrt((x - border[0]) / (radius[0] - (double)border[0]));
							double ty = std::pow(1 - t, 2) * radius[0] + 2 * (1 - t) * t * border[1] + std::pow(t, 2) * border[1];
							if (y < ty)
								return bplTop;
						}
						if (radius[1] > border[1] && x >= width - radius[1] && y < radius[1]) // Check point is in right-top corner
						{
							double t = std::sqrt((x - (width - 1) + border[2]) / ((double)border[2] - radius[1]));
							double ty = std::pow(1 - t, 2) * radius[1] + 2 * (1 - t) * t * border[1] + std::pow(t, 2) * border[1];
							if (y < ty)
								return bplTop;
						}
					}
			// Process bottom border
			if (y >= height - std::max(std::max(radius[2], radius[3]), border[3])) // Check point is in border & corners zone
				if (border[0] == 0 || y >= height - x * border[3] / border[0]) // Check point does not belongs to left border
					if (border[2] == 0 || y >= height - (width - x) * border[3] / border[2]) // Check point does not belongs to right border
					{
						if (radius[3] > 0 && x < radius[3] && y >= height - radius[3]) // Check point is out of left-bottom corner radius
						{
							double t = std::sqrt(x / (double)radius[3]);
							double ty = std::pow(1 - t, 2) * (height - 1 - radius[3]) + 2 * (1 - t) * t * (height - 1) + std::pow(t, 2) * (height - 1);
							if (y >= ty)
								return bplOutside;
						}
						if (radius[2] > 0 && x >= width - radius[2] && y >= height - radius[2]) // Check point is out of right-bottom corner radius
						{
							double t = std::sqrt((width - 1 - x) / (double)radius[2]);
							double ty = std::pow(1 - t, 2) * (height - 1 - radius[2]) + 2 * (1 - t) * t * (height - 1) + std::pow(t, 2) * (height - 1);
							if (y >= ty)
								return bplOutside;
						}
						if (y >= height - border[3] || x < border[0] || x > width - border[2]) // Point is completely inside border
							return bplBottom;
						if (radius[3] > border[3] && x < radius[3] && y >= height - radius[3]) // Check point is in left-bottom corner
						{
							double t = std::sqrt((x - border[0]) / (radius[3] - (double)border[0]));
							double ty = std::pow(1 - t, 2) * (height - 1 - radius[3]) + 2 * (1 - t) * t * (height - 1 - border[3]) + std::pow(t, 2) * (height - 1 - border[3]);
							if (y > ty)
								return bplBottom;
						}
						if (radius[2] > border[3] && x >= width - radius[2] && y >= height - radius[2]) // Check point is in right-bottom corner
						{
							double t = std::sqrt((x - (width - 1) + border[2]) / ((double)border[2] - radius[2]));
							double ty = std::pow(1 - t, 2) * (height - 1 - radius[2]) + 2 * (1 - t) * t * (height - 1 - border[3]) + std::pow(t, 2) * (height - 1 - border[3]);
							if (y > ty)
								return bplBottom;
						}
					}
			return bplInside;
		}

		/**
		@par Idea
		The idea of antializing is to extend block in several times(factor) and calc how much each location type of sub-point appears in block point
		*/
		void ClassifyBlockPoint(const int width, const int height, const int x, const int y, const math::RECTANGLE<int> &border, const math::RECTANGLE<int> &radius, const int factor, double *locations)
		{
#ifdef _DEBUG
			if (factor <= 0)
				throw "factor is invalid";
			if (!locations)
				throw "locations is null";
#endif
			int i, j;
			for (i = 0; i <= bplBottom; i++)
				locations[i] = 0;
			math::RECTANGLE<int> borders{ border[0] * factor, border[1] * factor, border[2] * factor, border[3] * factor };
			math::RECTANGLE<int> radiuses{ radius[0] * factor, radius[1] * factor, radius[2] * factor, radius[3] * factor };
			for (i = 0; i < factor; i++)
				for (j = 0; j < factor; j++)
					locations[ClassifyBlockPoint(width * factor, height * factor, x * factor + i, y * factor + i, borders, radiuses)]++;
			for (i = 0; i <= bplBottom; i++)
				locations[i] /= (float)factor * factor;
		}

		/**
		@par Idea and formulas:
		- For outer corner checks bezier n^2 curves are used(R - external radius bezier points):
		- Left-top corner: R1(0, radius[0]), R2(0, 0), R3(radius[0], 0)
		- Right-top corner: R1(width, radius[1]), R2(width, 0), R3(width - radius[1], 0)
		- Left-bottom corner: R1(0, height - radius[3]), R2(0, height), R3(radius[3], height)
		- Right-bottom corner: R1(width, height - radius[2]), R2(width, height), R3(width - radius[2], height)
		- P = (1 - t) * (1 - t) * P1 + 2 * (1 - t) * t * P2 + t * t * P3 - Bezier curve
		- D = b * b - 4 * a * c - Discriminant
		- x = ( - b +- SQRT(D))/ (2 * a)
		- First search t by known x: Final formula(assuming x2 = x1 due to selected points) is t = SQRT((x - x1) / (x3 - x1))
		- Than search curve y: Final formula is y = (1 - t) ^ 2 * y1 + 2 * (1 - t) * t * y2 + t ^ 2 * y3
		- Finaly compare found y with current point y and deside where point is
		*/
		BLOCK_POINT_LOCATION ClassifyBlockPoint(const int width, const int height, const int x, const int y, const math::RECTANGLE<int> &radius)
		{
#ifdef _DEBUG
			if (width < 0)
				throw "width is invalid";
			if (height < 0)
				throw "height is invalid";
			if (radius[0] < 0)
				throw "radius[0] is invalid";
			if (radius[1] < 0)
				throw "radius[1] is invalid";
			if (radius[2] < 0)
				throw "radius[2] is invalid";
			if (radius[3] < 0)
				throw "radius[3] is invalid";
#endif
			// Check point is completely outside of block
			if (x < 0 || y < 0 || x >= width || y >= height)
				return bplOutside;
			// Process left border
			if (x < std::max(radius[0], radius[3])) // Check point is in border & corners zone
			{
				if (radius[0] > 0 && y < radius[0] && x < radius[0]) // Check point is out of lect-top corner radius
				{
					double t = std::sqrt(x / (double)radius[0]);
					double ty = std::pow(1 - t, 2) * radius[0];
					if (y <= ty)
						return bplOutside;
				}
				if (radius[3] > 0 && y >= height - radius[3] && x < radius[3]) // Check point is out of left-bottom corner radius
				{
					double t = std::sqrt(x / (double)radius[3]);
					double ty = std::pow(1 - t, 2) * (height - 1 - radius[3]) + 2 * (1 - t) * t * (height - 1) + std::pow(t, 2) * (height - 1);
					if (y >= ty)
						return bplOutside;
				}
			}
			// Process right border
			if (x >= width - std::max(radius[1], radius[2])) // Check point is in border & corners zone
			{
				if (radius[1] > 0 && y < radius[1] && x >= width - radius[1]) // Check point is out of right-top corner radius
				{
					double t = std::sqrt((width - 1 - x) / (double)radius[1]);
					double ty = std::pow(1 - t, 2) * radius[1];
					if (y <= ty)
						return bplOutside;
				}
				if (radius[2] > 0 && y >= height - radius[2] && x >= width - radius[2]) // Check point is out of right-bottom radius
				{
					double t = std::sqrt((width - 1 - x) / (double)radius[2]);
					double ty = std::pow(1 - t, 2) * (height - 1 - radius[2]) + 2 * (1 - t) * t * (height - 1) + std::pow(t, 2) * (height - 1);
					if (y >= ty)
						return bplOutside;
				}
			}
			// Process top border
			if (y < std::max(radius[0], radius[1])) // Check point is in border & corners zone
			{
				if (radius[0] > 0 && x < radius[0] && y < radius[0]) // Check point is out of left-top corner radius
				{
					double t = std::sqrt(x / (double)radius[0]);
					double ty = std::pow(1 - t, 2) * radius[0];
					if (y < ty)
						return bplOutside;
				}
				if (radius[1] > 0 && x >= width - radius[1] && y < radius[1]) // Check point is out of right-top corner radius
				{
					double t = std::sqrt((width - 1 - x) / (double)radius[1]);
					double ty = std::pow(1 - t, 2) * radius[1];
					if (y < ty)
						return bplOutside;
				}
			}
			// Process bottom border
			if (y >= height - std::max(radius[2], radius[3])) // Check point is in border & corners zone
			{
				if (radius[3] > 0 && x < radius[3] && y >= height - radius[3]) // Check point is out of left-bottom corner radius
				{
					double t = std::sqrt(x / (double)radius[3]);
					double ty = std::pow(1 - t, 2) * (height - 1 - radius[3]) + 2 * (1 - t) * t * (height - 1) + std::pow(t, 2) * (height - 1);
					if (y >= ty)
						return bplOutside;
				}
				if (radius[2] > 0 && x >= width - radius[2] && y >= height - radius[2]) // Check point is out of right-bottom corner radius
				{
					double t = std::sqrt((width - 1 - x) / (double)radius[2]);
					double ty = std::pow(1 - t, 2) * (height - 1 - radius[2]) + 2 * (1 - t) * t * (height - 1) + std::pow(t, 2) * (height - 1);
					if (y >= ty)
						return bplOutside;
				}
			}
			return bplInside;
		}

		/**
		@par Idea
		The idea of antializing is to extend block in several times(factor) and calc how much each location type of sub-point appears in block point
		*/
		void ClassifyBlockPoint(const int width, const int height, const int x, const int y, const math::RECTANGLE<int> &radius, const int factor, double &inside, double &outside)
		{
#ifdef _DEBUG
			if (factor <= 0)
				throw "factor is invalid";
#endif
			int i, j;
			inside = outside = 0.0f;
			math::RECTANGLE<int> radiuses{ radius[0] * factor, radius[1] * factor, radius[2] * factor, radius[3] * factor };
			for (i = 0; i < factor; i++)
				for (j = 0; j < factor; j++)
					if (ClassifyBlockPoint(width * factor, height * factor, x * factor + i, y * factor + i, radiuses) == bplInside)
						inside++;
					else
						outside++;
			inside /= (float)factor * factor;
			outside /= (float)factor * factor;
		}
	}
}