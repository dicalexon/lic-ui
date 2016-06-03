// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "ImageMemory.h"
#include "Font.h"
#include "..\Math\Utils.h"

namespace licui
{
	namespace application
	{
#pragma region Global functions
		/**
		Get text alpha channel value at specified point(in global coordinates which are transformed into text local coordinates)
		@param x X global coordinate
		@param x Y global coordinate
		@param str Text to render
		@param font Font used for rendering
		@param channel Rendering channel. 0 - text, 1 - shadow
		@param m Matrix used for transforming from global coordinates to text local one
		@return Average point alpha channel value in range 0..1
		@note Bilinear interpolation is used to get alpha if font->getInterpolation() is on
		*/
		double GetTextAlpha(const double x, const double y, const String &str, IFont *font, const size_t channel, const APP_MATRIX &m)
		{
			IFont::GLYPH *glyph;
			int disp{ 0 }, tx1, ty1, tx2, ty2, char_x{ 0 }, count{ 0 };
			double dx, dy, a, a1, a2, a3, a4;
			APP_VECTOR v{ x, y, 1 };
			v = v * m;
			// Find char and paint on text
			double alpha{ 0 };
			for (wchar_t c : str)
			{
				glyph = font->getChar(c);
				if (!glyph)
					continue;
				if (v[0] < char_x || v[0] >= char_x + glyph->Image.getWidth()) // If point is out of glyph, go to next glyph
				{
					char_x += glyph->Width + font->getDistance();
					continue;
				}
				if (v[1] < 0 || v[1] >= glyph->Image.getHeight()) // If point is out of text by Y coordinate, go to next glyph
				{
					char_x += glyph->Width + font->getDistance();
					continue;
				}
				// Get best alpha depending wether interpolation is on or off
				tx1 = (int)v[0] - char_x;
				ty1 = (int)v[1];
				if (font->getInterpolate())
				{
					dx = v[0] - char_x - tx1;
					dy = v[1] - ty1;
					tx2 = tx1 + 1;
					ty2 = ty1 + 1;
					a1 = glyph->Image[tx1][ty1][channel];
					a2 = tx2 >= (int)glyph->Image.getWidth() ? 0 : glyph->Image[tx2][ty1][channel];
					a3 = ty2 >= (int)glyph->Image.getHeight() ? 0 : glyph->Image[tx1][ty2][channel];
					a4 = tx2 >= (int)glyph->Image.getWidth() || ty2 >= (int)glyph->Image.getHeight() ? 0 : glyph->Image[tx2][ty2][channel];
					a = (a1 * (1 - dx) + a2 * dx) * (1 - dy) + (a3 * (1 - dx) + a4 * dx) * dy;
				}
				else
					a = glyph->Image[tx1][ty1][channel];
				count == 0 ? alpha = a : alpha = (alpha * count + a) / (count + 1.0);
				count++;
				char_x += glyph->Width + font->getDistance();
			}
			return alpha;
		}
#pragma endregion

#pragma region CImageMemory::DATA
		CImageMemory::DATA::DATA() :alpha{ nullptr }, alpha_size{ 0 }, Locations{ 0, 1, 0, 0, 0, 0 }
		{

		}

		CImageMemory::DATA::~DATA()
		{
			if (alpha)
				delete[] alpha;
		}

		void CImageMemory::DATA::AllocAlpha(const size_t size)
		{
			if (alpha)
			{
				delete[] alpha;
				alpha = nullptr;
				alpha_size = 0;
			}
			if (size > 0)
			{
				alpha = new double[size * size];
				alpha_size = size;
			}
		}

		void CImageMemory::DATA::ClearAlpha()
		{
			for (size_t i = 0; i < alpha_size << 1; i++)
				alpha[i] = 0;
		}
#pragma endregion

#pragma region Constructors
		CImageMemory::CImageMemory()
		{

		}

		CImageMemory::CImageMemory(const size_t width, const size_t height, const String &name) :
			m_sName{ name }
		{
			m_sImage.Alloc(width, height);
		}
#pragma endregion

#pragma region Getters
		graphics::IMAGE<unsigned char, 4> &CImageMemory::getImage()
		{
			return m_sImage;
		}
#pragma endregion

#pragma region Helpers
		void CImageMemory::Alloc(const size_t width, const size_t height)
		{
			m_sImage.Alloc(width, height);
		}
#pragma endregion

#pragma region Required members
		size_t CImageMemory::getWidth() const
		{
			return m_sImage.getWidth();
		}

		size_t CImageMemory::getHeight() const
		{
			return m_sImage.getHeight();
		}

		String CImageMemory::getName() const
		{
			return m_sName;
		}

		IImage::FORMAT CImageMemory::getFormat() const
		{
			return{ "RGBA" };
		}

		APP_COLOR &CImageMemory::getPixel(const size_t x, const size_t y)
		{
			return m_sImage[x][y];
		}

		const APP_COLOR &CImageMemory::getPixel(const size_t x, const size_t y) const
		{
			return m_sImage[x][y];
		}

		bool CImageMemory::getIsValid() const
		{
			return m_sImage.getWidth() > 0;
		}

		void CImageMemory::setPixel(const size_t x, const size_t y, const APP_COLOR &value)
		{
			m_sImage[x][y] = value;
		}

		void CImageMemory::setPixel(const size_t x, const size_t y, const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
		{
			m_sImage.setPixel(x, y, r, g, b, a);
		}

		void CImageMemory::BlendPixel(const size_t x, const size_t y, const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
		{
			m_sImage.BlendPixel(x, y, r, g, b, a, 255);
		}

		void CImageMemory::BlendPixel(const size_t x, const size_t y, const APP_COLOR &color)
		{
			m_sImage.BlendPixel(x, y, color, 255);
		}

		IImage::LOCK *CImageMemory::Lock(const size_t x, const size_t y, const size_t width, const size_t height, const FORMAT &format)
		{
			if (!m_sImage.getWidth() || format != "RGBA")
				return nullptr;
			IImage::LOCK *result{ new IImage::LOCK };
			result->Data = &m_sImage[0][0];
			result->X = 0;
			result->Y = 0;
			result->Width = m_sImage.getWidth();
			result->Height = m_sImage.getHeight();
			result->Pitch = m_sImage.getWidth() >> 2;
			result->Format = { "RGBA" };
			return result;
		}

		void CImageMemory::Unlock(LOCK *lock)
		{
			if (lock)
				delete lock;
		}

		void CImageMemory::Release()
		{
			delete this;
		}

		bool CImageMemory::BeginPaint()
		{
			return true;
		}

		void CImageMemory::EndPaint()
		{

		}

		void CImageMemory::Clear(const APP_COLOR &value)
		{
			m_sImage.Fill(value);
		}
#pragma endregion

#pragma region Helper methods
		void CImageMemory::FillBlockData(DATA &data, const size_t width, const size_t height, const math::RECTANGLE<size_t> &border, const math::RECTANGLE<size_t> &radius, const size_t antialiazing, const graphics::BLOCK_POINT_LOCATION location)
		{
			data.Width = width;
			data.Height = height;
			data.Border[0] = border[0];
			data.Border[1] = border[1];
			data.Border[2] = border[2];
			data.Border[3] = border[3];
			data.Radius[0] = radius[0];
			data.Radius[1] = radius[1];
			data.Radius[2] = radius[2];
			data.Radius[3] = radius[3];
			data.AntiAliazing = antialiazing;
			data.Location = location;
		}

		void CImageMemory::FillTextData(DATA &data, const size_t antialiazing, IFont *font, const String *text, const size_t channel, APP_MATRIX &matrix)
		{
			data.TextAntialiazing = antialiazing;
			data.TextFont = font;
			data.Text = text;
			data.TextChannel = channel;
			data.Matrix = matrix;
			data.AllocAlpha(antialiazing);
		}

		void CImageMemory::FillImageData(DATA &data, IImage *image, const APP_RECT &image_part, const int x, const int y, const bool repeat_x, const bool repeat_y)
		{
			data.Image = &((CImageMemory*)image)->getImage();
			data.ImagePart = image_part;
			data.ImageX = x;
			data.ImageY = y;
			data.ImageRepeatX = repeat_x;
			data.ImageRepeatY = repeat_y;
		}

		void CImageMemory::FillGradientData(DATA &data, const APP_RECT &rect, const size_t point_count, const GRADIENT_TYPE type, const GRADIENT_POINT *points)
		{
			data.GradientRect = rect;
			data.GradientPointCount = point_count;
			data.GradientType = type;
			data.GradientPoints = points;
		}

		CImageMemory::FClassify CImageMemory::SelectClassify(const DATA &data)
		{
			if (data.Border[0] == 0 && data.Border[1] == 0 && data.Border[2] == 0 && data.Border[3] == 0 && data.Radius[0] == 0 && data.Radius[1] == 0 && data.Radius[2] == 0 && data.Radius[3] == 0)
				return [](const int x, const int y, DATA &data)
			{
				data.Locations[data.Location] = (data.Location == graphics::bplInside && x >= 0 && x < data.Width && y >= 0 && y < data.Height) ? 1.0 : 0.0;
				return data.Locations[data.Location];
			};
			if (data.AntiAliazing > 1)
			{
				if (data.Border[0] > 0 || data.Border[1] > 0 || data.Border[2] > 0 || data.Border[3] > 0)
				{
					return [](const int x, const int y, DATA &data)
					{
						graphics::ClassifyBlockPoint(data.Width, data.Height, x, y, data.Border, data.Radius, data.AntiAliazing, &data.Locations[0]);
						return data.Locations[data.Location];
					};
				}
				return [](const int x, const int y, DATA &data)
				{
					graphics::ClassifyBlockPoint(data.Width, data.Height, x, y, data.Radius, data.AntiAliazing, data.Locations[graphics::bplInside], data.Locations[graphics::bplOutside]);
					return data.Locations[data.Location];
				};
			}
			if (data.Border[0] > 0 || data.Border[1] > 0 || data.Border[2] > 0 || data.Border[3] > 0)
			{
				return [](const int x, const int y, DATA &data)
				{
					for (size_t l = 0; l <= graphics::bplBottom; l++)
						data.Locations[l] = 0;
					data.Locations[graphics::ClassifyBlockPoint(data.Width, data.Height, x, y, data.Border, data.Radius)] = 1;
					return data.Locations[data.Location];
				};
			}
			return [](const int x, const int y, DATA &data)
			{
				for (size_t l = 0; l <= graphics::bplBottom; l++)
					data.Locations[l] = 0;
				data.Locations[graphics::ClassifyBlockPoint(data.Width, data.Height, x, y, data.Radius)] = 1;
				return data.Locations[data.Location];
			};
		}

		CImageMemory::FGetAlpha CImageMemory::SelectTextGetAlpha(DATA &data, const double angle)
		{
			if (data.TextAntialiazing > 1 && angle != 0)
				return [](const int x, const int y, DATA &data)
			{
				for (data.i = 0; data.i < data.TextAntialiazing; data.i++)
					for (data.j = 0; data.j < data.TextAntialiazing; data.j++)
						data.alpha[data.j * data.TextAntialiazing + data.i] = GetTextAlpha(x + data.i / (double)data.TextAntialiazing, y + data.j / (double)data.TextAntialiazing, *data.Text, data.TextFont, data.TextChannel, data.Matrix);
				double a{ 0 };
				for (data.i = 0; data.i < data.TextAntialiazing; data.i++)
					for (data.j = 0; data.j < data.TextAntialiazing; data.j++)
						a += data.alpha[data.j * data.TextAntialiazing + data.i];
				a /= data.TextAntialiazing * data.TextAntialiazing;
				return a;
			};
			return [](const int x, const int y, DATA &data)
			{
				return GetTextAlpha(x, y, *(data.Text), data.TextFont, data.TextChannel, data.Matrix);
			};
		}

		CImageMemory::FGetPixel CImageMemory::SelectGetPixel(DATA &data, const double angle, const double sx, const double sy, const bool interpolate)
		{
			if (angle == 0 && sx == 1 && sy == 1)
			{
				if (!data.ImageRepeatX && !data.ImageRepeatY)
				{
					return [](const int x, const int y, DATA &data) // No size change, no repeating
					{
						return (*data.Image)[x - data.ImageX + data.ImagePart.Left][y - data.ImageY + data.ImagePart.Top];
					};
				}
				return [](const int x, const int y, DATA &data) // No size change, have repeating
				{
					int tx{ x - data.ImageX + data.ImagePart.Left }, ty{ y - data.ImageX + data.ImagePart.Top };
					while (tx < data.ImagePart.Left)
						tx += data.ImagePart.Width();
					while (tx >= data.ImagePart.Right)
						tx -= data.ImagePart.Width();
					while (ty < data.ImagePart.Top)
						ty += data.ImagePart.Height();
					while (ty >= data.ImagePart.Bottom)
						ty -= data.ImagePart.Height();
					return (*data.Image)[tx][ty];
				};
			}
			if (!interpolate)
			{
				if (!data.ImageRepeatX && !data.ImageRepeatY)
				{
					return [](const int x, const int y, DATA &data) // Size is changed, no interpolation and no repeating
					{
						APP_VECTOR v{ (double)x, (double)y, 1 };
						v = v * data.Matrix;
						if (v[0] < data.ImagePart.Left || v[0] >= data.ImagePart.Right || v[1] < data.ImagePart.Top || v[1] >= data.ImagePart.Bottom)
						{
							APP_COLOR c{ 0, 0, 0, 0 };
							return c;
						}
						return (*data.Image)[(int)v[0]][(int)v[1]];
					};
				}
				return [](const int x, const int y, DATA &data) // Size is changed, no interpolation, have repeating
				{
					APP_VECTOR v{ (double)x, (double)y, 1 };
					v = v * data.Matrix;
					if ((!data.ImageRepeatX && (v[0] < data.ImagePart.Left || v[0] >= data.ImagePart.Right)) || (!data.ImageRepeatY && (v[1] < data.ImagePart.Top || v[1] >= data.ImagePart.Bottom)))
					{
						APP_COLOR c{ 0, 0, 0, 0 };
						return c;
					}
					while (v[0] < data.ImagePart.Left)
						v[0] += data.ImagePart.Width();
					while (v[0] >= data.ImagePart.Right)
						v[0] -= data.ImagePart.Width();
					while (v[1] < data.ImagePart.Top)
						v[1] += data.ImagePart.Height();
					while (v[1] >= data.ImagePart.Bottom)
						v[1] -= data.ImagePart.Height();
					return (*data.Image)[(int)v[0]][(int)v[1]];
				};
			}
			return [](const int x, const int y, DATA &data) // Size is changed, have interpolation and have or have no repeating
			{
				APP_VECTOR v{ (double)x, (double)y, 1 };
				v = v * data.Matrix;
				if ((!data.ImageRepeatX && (v[0] < data.ImagePart.Left || v[0] >= data.ImagePart.Right)) || (!data.ImageRepeatY && (v[1] < data.ImagePart.Top || v[1] >= data.ImagePart.Bottom)))
				{
					APP_COLOR c{ 0, 0, 0, 0 };
					return c;
				}
				while (v[0] < data.ImagePart.Left)
					v[0] += data.ImagePart.Width();
				while (v[0] >= data.ImagePart.Right)
					v[0] -= data.ImagePart.Width();
				while (v[1] < data.ImagePart.Top)
					v[1] += data.ImagePart.Height();
				while (v[1] >= data.ImagePart.Bottom)
					v[1] -= data.ImagePart.Height();
				// Adjust to image size - 1 to have equal color ranges even on the ends of image
				if (data.ImagePart.Width() > 1)
					v[0] = data.ImagePart.Left + (v[0] - data.ImagePart.Left) / data.ImagePart.Width() * (data.ImagePart.Width() - 1);
				if (data.ImagePart.Height() > 1)
					v[1] = data.ImagePart.Top + (v[1] - data.ImagePart.Top) / data.ImagePart.Height() * (data.ImagePart.Height() - 1);
				// Get points coordinates
				int tx1{ (int)v[0] }, ty1{ (int)v[1] };
				double dx{ v[0] - tx1 }, dy{ v[1] - ty1 };
				int tx2{ tx1 + 1 }, ty2{ ty1 + 1 };
				// Get points colors
				APP_COLOR c1 = (*data.Image)[tx1][ty1], c2, c3, c4, c;
				tx2 >= data.ImagePart.Right ? c2 = (*data.Image)[tx1][ty1] : c2 = (*data.Image)[tx2][ty1];
				if (ty2 >= data.ImagePart.Bottom)
				{
					c3 = (*data.Image)[tx1][ty1];
					tx2 >= data.ImagePart.Right ? c4 = (*data.Image)[tx1][ty1] : c4 = (*data.Image)[tx2][ty1];
				}
				else
				{
					c3 = (*data.Image)[tx1][ty2];
					tx2 >= data.ImagePart.Right ? c4 = (*data.Image)[tx1][ty2] : c4 = (*data.Image)[tx2][ty2];
				}
				// Calc final color
				c[0] = (unsigned char)((c1[0] * (1 - dx) + c2[0] * dx) * (1 - dy) + (c3[0] * (1 - dx) + c4[0] * dx) * dy);
				c[1] = (unsigned char)((c1[1] * (1 - dx) + c2[1] * dx) * (1 - dy) + (c3[1] * (1 - dx) + c4[1] * dx) * dy);
				c[2] = (unsigned char)((c1[2] * (1 - dx) + c2[2] * dx) * (1 - dy) + (c3[2] * (1 - dx) + c4[2] * dx) * dy);
				c[3] = (unsigned char)((c1[3] * (1 - dx) + c2[3] * dx) * (1 - dy) + (c3[3] * (1 - dx) + c4[3] * dx) * dy);
				return c;
			};
		}

		APP_MATRIX CImageMemory::CreateTransformation(const double x1, const double y1, const double angle, const double sx, const double sy, const double x2, const double y2)
		{
			APP_MATRIX m{ 3, 3 }, r{ 3, 3 }, t1{ 3, 3 }, t2{ 3, 3 }, s{ 3, 3 };
			r.RotateZ(angle);
			t1.Translate(x1, y1);
			t2.Translate(x2, y2);
			s.Scale(sx, sy);
			m = t1 * s * r * t2;
			m.Inverse();
			return m;
		}

		void CImageMemory::SelectBorderRanges(const DATA &data, const APP_RECT &block_rect, const APP_RECT &clip, int &x1_from, int &x1_to, int &x2_from, int &x2_to, int &x3_from, int &x3_to, int &y1_from, int &y1_to, int &y2_from, int &y2_to, int &y3_from, int &y3_to)
		{
			switch (data.Location)
			{
			case graphics::bplLeft:
				x1_from = block_rect.Left;
				x1_to = block_rect.Left + std::max(data.Radius[0], data.Border.Left);
				y1_from = block_rect.Top;
				y1_to = block_rect.Top + std::max(data.Radius[0], data.Border.Top);

				x2_from = block_rect.Left;
				x2_to = block_rect.Left + data.Border.Left;
				y2_from = block_rect.Top + std::max(data.Radius[0], data.Border.Top);
				y2_to = block_rect.Bottom - std::max(data.Radius[3], data.Border.Bottom);

				x3_from = block_rect.Left;
				x3_to = block_rect.Left + std::max(data.Radius[3], data.Border.Left);
				y3_from = block_rect.Bottom - std::max(data.Radius[3], data.Border.Bottom);
				y3_to = block_rect.Bottom;
				break;
			case graphics::bplTop:
				x1_from = block_rect.Left;
				x1_to = block_rect.Left + std::max(data.Radius[0], data.Border.Left);
				y1_from = block_rect.Top;
				y1_to = block_rect.Top + std::max(data.Radius[0], data.Border.Top);

				x2_from = block_rect.Left + std::max(data.Radius[0], data.Border.Left);
				x2_to = block_rect.Right - std::max(data.Radius[1], data.Border.Right);
				y2_from = block_rect.Top;
				y2_to = block_rect.Top + data.Border.Top;

				x3_from = block_rect.Right - std::max(data.Radius[1], data.Border.Right);
				x3_to = block_rect.Right;
				y3_from = block_rect.Top;
				y3_to = block_rect.Top + std::max(data.Radius[1], data.Border.Top);
				break;
			case graphics::bplRight:
				x1_from = block_rect.Right - std::max(data.Radius[1], data.Border.Right);
				x1_to = block_rect.Right;
				y1_from = block_rect.Top;
				y1_to = block_rect.Top + std::max(data.Radius[1], data.Border.Top);

				x2_from = block_rect.Right - data.Border.Right;
				x2_to = block_rect.Right;
				y2_from = block_rect.Top + std::max(data.Radius[1], data.Border.Top);
				y2_to = block_rect.Bottom - std::max(data.Radius[2], data.Border.Bottom);

				x3_from = block_rect.Right - std::max(data.Radius[2], data.Border.Right);
				x3_to = block_rect.Right;
				y3_from = block_rect.Bottom - std::max(data.Radius[2], data.Border.Bottom);
				y3_to = block_rect.Bottom;
				break;
			case graphics::bplBottom:
				x1_from = block_rect.Left;
				x1_to = block_rect.Left + std::max(data.Radius[3], data.Border.Left);
				y1_from = block_rect.Bottom - std::max(data.Radius[3], data.Border.Bottom);
				y1_to = block_rect.Bottom;

				x2_from = block_rect.Left + std::max(data.Radius[3], data.Border.Left);
				x2_to = block_rect.Right - std::max(data.Radius[2], data.Border.Right);
				y2_from = block_rect.Bottom - data.Border.Bottom;
				y2_to = block_rect.Bottom;

				x3_from = block_rect.Right - std::max(data.Radius[2], data.Border.Right);
				x3_to = block_rect.Right;
				y3_from = block_rect.Bottom - std::max(data.Radius[2], data.Border.Bottom);
				y3_to = block_rect.Bottom;
				break;
			}
			x1_from = std::min(std::max(x1_from, clip.Left), clip.Right);
			x1_to = std::min(std::max(x1_to, clip.Left), clip.Right);
			y1_from = std::min(std::max(y1_from, clip.Top), clip.Bottom);
			y1_to = std::min(std::max(y1_to, clip.Top), clip.Bottom);

			x2_from = std::min(std::max(x2_from, clip.Left), clip.Right);
			x2_to = std::min(std::max(x2_to, clip.Left), clip.Right);
			y2_from = std::min(std::max(y2_from, clip.Top), clip.Bottom);
			y2_to = std::min(std::max(y2_to, clip.Top), clip.Bottom);

			x3_from = std::min(std::max(x3_from, clip.Left), clip.Right);
			x3_to = std::min(std::max(x3_to, clip.Left), clip.Right);
			y3_from = std::min(std::max(y3_from, clip.Top), clip.Bottom);
			y3_to = std::min(std::max(y3_to, clip.Top), clip.Bottom);
		}

		APP_COLOR CImageMemory::CalculateGradient(const int x, const int y, DATA &data)
		{
			size_t i1{ 0 }, i2{ 1 }, i;
			double d{ 0 }, t;
			switch (data.GradientType)
			{
			case gtVertical:
				d = ((double)y - (double)data.GradientRect.Top) / (double)data.GradientRect.Height();
				break;
			case gtRadial:
			{
				double x0{ (double)x - ((double)data.GradientRect.Left + (double)data.GradientRect.Right) * 0.5 };
				double y0{ (double)y - ((double)data.GradientRect.Top + (double)data.GradientRect.Bottom) * 0.5 };
				double dx{ (double)data.GradientRect.Right - (double)data.GradientRect.Left };
				double dy{ (double)data.GradientRect.Bottom - (double)data.GradientRect.Top };
				d = std::sqrt((x0 * x0 + y0 * y0) / (dx * dx + dy * dy));
				break;
			}
			case gtDiagonalDown:
			{
				math::POINT<double> b{ (double)data.GradientRect.Right - (double)data.GradientRect.Left, (double)data.GradientRect.Bottom - (double)data.GradientRect.Top };
				math::POINT<double> a{ (double)x - (double)data.GradientRect.Left, (double)y - (double)data.GradientRect.Top };
				d = (a.X * b.X + a.Y * b.Y) / std::sqrt(b.X * b.X + b.Y * b.Y);
				break;
			}
			case gtDiagonalUp:
			{
				math::POINT<double> b{ (double)data.GradientRect.Right - (double)data.GradientRect.Left, (double)data.GradientRect.Top - (double)data.GradientRect.Bottom };
				math::POINT<double> a{ (double)x - (double)data.GradientRect.Left, (double)y - (double)data.GradientRect.Bottom };
				d = (a.X * b.X + a.Y * b.Y) / std::sqrt(b.X * b.X + b.Y * b.Y);
				break;
			}
			default: //gtHorizontal
				d = ((double)x - (double)data.GradientRect.Left) / (double)data.GradientRect.Width();
				break;
			}
			for (i = 1; i < data.GradientPointCount; i++)
				if (data.GradientPoints[i].Position >= d)
				{
					i1 = i - 1;
					i2 = i;
					break;
				}
			t = (d - data.GradientPoints[i1].Position) / (data.GradientPoints[i2].Position - data.GradientPoints[i1].Position);
			return APP_COLOR{
				(unsigned char)(data.GradientPoints[i1].Color[0] * (1 - t) + data.GradientPoints[i2].Color[0] * t),
				(unsigned char)(data.GradientPoints[i1].Color[1] * (1 - t) + data.GradientPoints[i2].Color[1] * t),
				(unsigned char)(data.GradientPoints[i1].Color[2] * (1 - t) + data.GradientPoints[i2].Color[2] * t),
				(unsigned char)(data.GradientPoints[i1].Color[3] * (1 - t) + data.GradientPoints[i2].Color[3] * t)
			};
		}
#pragma endregion

#pragma region Text
		void CImageMemory::RenderString(
			const String &str,
			IFont *font,
			const double x,
			const double y,
			const double angle,
			const double sx,
			const double sy,
			APP_RECT clip,
			const size_t antialiazing,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_width,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			const graphics::BLOCK_POINT_LOCATION location,
			const bool draw_text,
			const bool draw_shadow,
			const APP_COLOR &text_color,
			const APP_COLOR &shadow_color,
			ICustomClip *fclip,
			ICustomRender *frender,
			const bool blend)
		{
			if (m_sImage.getWidth() > 0 && font && !clip.IsEmpty() && clip.IsValid() && !str.empty() && m_sImage.getWidth() > 0 && block_rect.IsValid() && !block_rect.IsEmpty() &&
				block_rect.Width() > (int)border_width[0] + (int)border_width[2] && block_rect.Height() > (int)border_width[1] + (int)border_width[3])
			{
				APP_POINT size_o = font->getStringSize(str);
				APP_POINT size_r{ (int)(size_o.X * sx + 0.5), (int)(size_o.Y * sy + 0.5) };
				size_r = math::RotatedRectangleSize(size_r, angle); // Get rotated string size
				if (size_o.X <= 0 || size_o.Y <= 0 || size_r.X <= 0 || size_r.Y <= 0) // If any of size is invalid, render nothing
					return;
				clip *= {0, 0, (int)m_sImage.getWidth(), (int)m_sImage.getHeight()}; // Adjust clip to fit buffer
				clip *= block_rect;
				if (draw_shadow && font->getShadow() && shadow_color.getAlpha() > 0)
					InternalRenderString(str, font, x, y, angle, sx, sy, clip, antialiazing, block_rect, border_width, border_radius, border_antialiazing, location, 1, shadow_color, size_o, size_r, fclip, frender, blend);
				if (draw_text && text_color.getAlpha() > 0)
					InternalRenderString(str, font, x, y, angle, sx, sy, clip, antialiazing, block_rect, border_width, border_radius, border_antialiazing, location, 0, text_color, size_o, size_r, fclip, frender, blend);
			}
		}

		void CImageMemory::InternalRenderString(
			const String &str,
			IFont *font,
			const double x,
			const double y,
			const double angle,
			const double sx,
			const double sy,
			const APP_RECT &clip,
			const size_t antialiazing,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_width,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			const graphics::BLOCK_POINT_LOCATION location,
			const size_t channel,
			const APP_COLOR &color,
			const APP_POINT &size_o,
			const APP_POINT &size_r,
			ICustomClip *fclip,
			ICustomRender *frender,
			const bool blend)
		{
			int tx, ty;
			double a, clip_alpha{ 1 };
			DATA data;
			FillBlockData(data, block_rect.Width(), block_rect.Height(), border_width, border_radius, border_antialiazing, location);
			FClassify classify = SelectClassify(data);
			if (!fclip && !frender)
			{
				// No custom clipping or rendering
				if (angle == 0 && sx == 1 && sy == 1)
				{
					// Text is translated only(no antialiazing is required, draw chars)
					IFont::GLYPH *glyph;
					int char_x{ int(x) }, y1{ std::max(clip.Top, (int)y) }, y2, x1, x2;
					for (wchar_t c : str)
					{
						glyph = font->getChar(c);
						if (!glyph)
							continue;
						if (char_x + (int)glyph->Image.getWidth() < clip.Left || char_x >= clip.Right) // If point is out of glyph, go to next glyph
						{
							char_x += glyph->Width + font->getDistance();
							continue;
						}
						y2 = std::min(clip.Bottom, (int)y + (int)glyph->Image.getHeight());
						x1 = std::max(clip.Left, char_x);
						x2 = std::min(clip.Right, char_x + (int)glyph->Image.getWidth());
						for (ty = y1; ty < y2; ty++)
							for (tx = x1; tx < x2; tx++)
							{
								if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
									continue;
								a = glyph->Image[tx - char_x][ty - (int)y][channel] * clip_alpha;
								if (a > 0)
									if (blend)
										m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0), 255);
									else
										m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0));
							}
						char_x += glyph->Width + font->getDistance();
					}
				}
				else
				{
					// Text is scaled or rotated(antialiazing is required, draw clipping rectangle)
					APP_MATRIX m = CreateTransformation(-size_o.X * 0.5, -size_o.Y * 0.5, angle, sx, sy, size_r.X * 0.5 + x, size_r.Y * 0.5 + y);
					FillTextData(data, antialiazing, font, &str, channel, m);
					FGetAlpha get_alpha = SelectTextGetAlpha(data, angle);

					for (ty = clip.Top; ty < clip.Bottom; ty++)
						for (tx = clip.Left; tx < clip.Right; tx++)
						{
							if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
								continue;
							a = get_alpha(tx, ty, data) * clip_alpha;
							if (a > 0)
								if (blend)
									m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0), 255);
								else
									m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0));
						}
				}
			}
			else
			{
				// Have custom clipping or rendering
				if (angle == 0 && sx == 1 && sy == 1)
				{
					// Text is translated only(no antialiazing is required, draw chars)
					IFont::GLYPH *glyph;
					int char_x{ int(x) }, y1{ std::max(clip.Top, (int)y) }, y2, x1, x2;
					for (wchar_t c : str)
					{
						glyph = font->getChar(c);
						if (!glyph)
							continue;
						if (char_x + (int)glyph->Image.getWidth() < clip.Left || char_x >= clip.Right) // If point is out of glyph, go to next glyph
						{
							char_x += glyph->Width + font->getDistance();
							continue;
						}
						y2 = std::min(clip.Bottom, (int)y + (int)glyph->Image.getHeight());
						x1 = std::max(clip.Left, char_x);
						x2 = std::min(clip.Right, char_x + (int)glyph->Image.getWidth());
						for (ty = y1; ty < y2; ty++)
							for (tx = x1; tx < x2; tx++)
							{
								if (fclip && !fclip->Check(tx, ty, location))
									continue;
								if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
									continue;
								a = glyph->Image[tx - char_x][ty - (int)y][channel] * clip_alpha;
								if (a > 0)
									if (frender)
										frender->Render(this, tx, ty, { color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0) });
									else
										if (blend)
											m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0), 255);
										else
											m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0));
							}
						char_x += glyph->Width + font->getDistance();
					}
				}
				else
				{
					// Text is scaled or rotated(antialiazing is required, draw clipping rectangle)
					APP_MATRIX m = CreateTransformation(-size_o.X * 0.5, -size_o.Y * 0.5, angle, sx, sy, size_r.X * 0.5 + x, size_r.Y * 0.5 + y);
					FillTextData(data, antialiazing, font, &str, channel, m);
					FGetAlpha get_alpha = SelectTextGetAlpha(data, angle);

					for (ty = clip.Top; ty < clip.Bottom; ty++)
						for (tx = clip.Left; tx < clip.Right; tx++)
						{
							if (fclip && !fclip->Check(tx, ty, location))
								continue;
							if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
								continue;
							a = get_alpha(tx, ty, data) * clip_alpha;
							if (a > 0)
								if (frender)
									frender->Render(this, tx, ty, { color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0) });
								else
									if (blend)
										m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0), 255);
									else
										m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)((color.getAlpha() * a) / 255.0));
						}
				}
			}
		}
#pragma endregion

#pragma region Image
		void CImageMemory::RenderImage(
			IImage *image,
			APP_RECT image_part,
			const double x,
			const double y,
			const double angle,
			const double sx,
			const double sy,
			const bool repeat_x,
			const bool repeat_y,
			const bool interpolate,
			APP_RECT clip,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_width,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			const graphics::BLOCK_POINT_LOCATION location,
			ICustomClip *fclip,
			ICustomRender *frender,
			const bool blend)
		{
			// Check buffer, image, image part, and block rect are valid
			if (image && m_sImage.getWidth() == 0 || image->getWidth() == 0 || !image_part.IsValid() || image_part.IsEmpty() || !block_rect.IsValid() || block_rect.IsEmpty())
				return;
			// Adjust image part to image bounds and check it is valid
			image_part = { std::max(0, image_part.Left), std::max(0, image_part.Top), std::min((int)image->getWidth(), image_part.Right), std::min((int)image->getHeight(), image_part.Bottom) };
			if (!image_part.IsValid() || image_part.IsEmpty())
				return;
			// Adjust clip rect
			clip *= {0, 0, (int)m_sImage.getWidth(), (int)m_sImage.getHeight() };
			clip *= block_rect;
			if (angle == 0 && sx == 1 && !repeat_x)
				clip *= {(int)x, clip.Top, (int)x + image_part.Width(), clip.Bottom};
			if (angle == 0 && sy == 1 && !repeat_y)
				clip *= {clip.Left, (int)y, clip.Right, (int)y + image_part.Height()};
			// Vars
			int tx, ty;
			APP_COLOR c;
			double clip_alpha;
			DATA data;
			FillBlockData(data, block_rect.Width(), block_rect.Height(), border_width, border_radius, border_antialiazing, location);
			FillImageData(data, image, image_part, (int)x, (int)y, repeat_x, repeat_y);
			FClassify classify = SelectClassify(data);
			FGetPixel get_pixel = SelectGetPixel(data, angle, sx, sy, interpolate);
			math::POINT<double> p{ (double)image_part.Width() * sx, (double)image_part.Height() * sy };
			p = math::RotatedRectangleSize(p, angle);
			data.Matrix = CreateTransformation(-(image_part.Left + image_part.Right) * 0.5, -(image_part.Top + image_part.Bottom) * 0.5, angle, sx, sy, x + p.X * 0.5, y + p.Y * 0.5);
			// Rendering
			if (!fclip && !frender)
				for (ty = clip.Top; ty < clip.Bottom; ty++)
					for (tx = clip.Left; tx < clip.Right; tx++)
					{
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						c = get_pixel(tx, ty, data);
						c.setAlpha((unsigned char)(c.getAlpha() * clip_alpha));
						if (blend)
							m_sImage.BlendPixel(tx, ty, c, 255);
						else
							m_sImage[tx][ty] = c;
					}
			else
				for (ty = clip.Top; ty < clip.Bottom; ty++)
					for (tx = clip.Left; tx < clip.Right; tx++)
					{
						if (fclip && !fclip->Check(tx, ty, location))
							continue;
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						c = get_pixel(tx, ty, data);
						c.setAlpha((unsigned char)(c.getAlpha() * clip_alpha));
						if (frender)
							frender->Render(this, tx, ty, c);
						else
							if (blend)
								m_sImage.BlendPixel(tx, ty, c, 255);
							else
								m_sImage[tx][ty] = c;
					}
		}
#pragma endregion

#pragma region Fill rectangle
		void CImageMemory::FillRect(
			const APP_COLOR &color,
			APP_RECT clip,
			const APP_RECT &rect,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_width,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			const graphics::BLOCK_POINT_LOCATION location,
			ICustomClip *fclip,
			ICustomRender *frender,
			const bool blend)
		{
			// Check buffer and block rect are valid
			if (m_sImage.getWidth() == 0 || !block_rect.IsValid() || block_rect.IsEmpty())
				return;
			// Adjust clip rect
			clip *= {0, 0, (int)m_sImage.getWidth(), (int)m_sImage.getHeight()};
			clip *= rect;
			clip *= block_rect;
			switch (location)
			{
			case graphics::bplInside:
				clip *= {block_rect.Left + (int)border_width[0], block_rect.Top + (int)border_width[1], block_rect.Right - (int)border_width[2], block_rect.Bottom - (int)border_width[3]};
				if (!clip.IsValid() || clip.IsEmpty())
					return;
				break;
			case graphics::bplLeft:
				clip *= {block_rect.Left, block_rect.Top, block_rect.Left + (int)std::max(std::max(border_radius[3], border_radius[0]), border_width[0]), block_rect.Bottom};
				if (!clip.IsValid() || clip.IsEmpty())
					return;
				break;
			case graphics::bplTop:
				clip *= {block_rect.Left, block_rect.Top, block_rect.Right, block_rect.Top + (int)std::max(std::max(border_radius[0], border_radius[1]), border_width[1])};
				if (!clip.IsValid() || clip.IsEmpty())
					return;
				break;
			case graphics::bplRight:
				clip *= {block_rect.Left - (int)std::min(std::min(border_radius[1], border_radius[2]), border_width[2]), block_rect.Top, block_rect.Right, block_rect.Bottom};
				if (!clip.IsValid() || clip.IsEmpty())
					return;
				break;
			case graphics::bplBottom:
				clip *= {block_rect.Left, block_rect.Top - (int)std::min(std::min(border_radius[2], border_radius[3]), border_width[3]), block_rect.Right, block_rect.Bottom};
				if (!clip.IsValid() || clip.IsEmpty())
					return;
				break;
			}
			// Vars
			int tx, ty;
			double clip_alpha;
			DATA data;
			FillBlockData(data, block_rect.Width(), block_rect.Height(), border_width, border_radius, border_antialiazing, location);
			FClassify classify = SelectClassify(data);
			// Rendering
			if (!fclip && !frender)
				for (ty = clip.Top; ty < clip.Bottom; ty++)
					for (tx = clip.Left; tx < clip.Right; tx++)
					{
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						if (blend)
							m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha), 255);
						else
							m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha));
					}
			else
				for (ty = clip.Top; ty < clip.Bottom; ty++)
					for (tx = clip.Left; tx < clip.Right; tx++)
					{
						if (fclip && !fclip->Check(tx, ty, location))
							continue;
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						if (frender)
							frender->Render(this, tx, ty, { color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha) });
						else
							if (blend)
								m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha), 255);
							else
								m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha));
					}
		}

		void CImageMemory::MultiFillRect(
			const APP_COLOR colors[graphics::bplBottom + 1],
			APP_RECT clip,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_width,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			ICustomClip *fclip,
			ICustomRender *frender,
			const bool blend)
		{
			// Check buffer and block rect are valid
			if (m_sImage.getWidth() == 0 || !block_rect.IsValid() || block_rect.IsEmpty())
				return;
			// Adjust clip rect
			clip *= {0, 0, (int)m_sImage.getWidth(), (int)m_sImage.getHeight()};
			clip *= block_rect;
			// Vars
			int tx, ty, i;
			DATA data;
			FillBlockData(data, block_rect.Width(), block_rect.Height(), border_width, border_radius, border_antialiazing, graphics::bplInside);
			FClassify classify = SelectClassify(data);
			// Rendering
			if (!fclip && !frender)
				for (ty = clip.Top; ty < clip.Bottom; ty++)
					for (tx = clip.Left; tx < clip.Right; tx++)
					{
						classify(tx - block_rect.Left, ty - block_rect.Top, data);
						for (i = 0; i <= graphics::bplBottom; i++)
							if (data.Locations[i] > 0 && colors[i].getAlpha() > 0)
								if (blend)
									m_sImage.BlendPixel(tx, ty, colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue(), (unsigned char)(colors[i].getAlpha() * data.Locations[i]), 255);
								else
									m_sImage.setPixel(tx, ty, colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue(), (unsigned char)(colors[i].getAlpha() * data.Locations[i]));
					}
			else
				for (ty = clip.Top; ty < clip.Bottom; ty++)
					for (tx = clip.Left; tx < clip.Right; tx++)
					{
						classify(tx - block_rect.Left, ty - block_rect.Top, data);
						for (i = 0; i <= graphics::bplBottom; i++)
							if (data.Locations[i] > 0 && colors[i].getAlpha() > 0)
							{
								if (fclip && !fclip->Check(tx, ty, (graphics::BLOCK_POINT_LOCATION)i))
									continue;
								if (frender)
									frender->Render(this, tx, ty, { colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue(), (unsigned char)(colors[i].getAlpha() * data.Locations[i]) });
								else
									if (blend)
										m_sImage.BlendPixel(tx, ty, colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue(), (unsigned char)(colors[i].getAlpha() * data.Locations[i]), 255);
									else
										m_sImage.setPixel(tx, ty, colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue(), (unsigned char)(colors[i].getAlpha() * data.Locations[i]));
							}
					}
		}

		void CImageMemory::RenderBorder(
			const graphics::BLOCK_POINT_LOCATION location,
			const APP_COLOR &color,
			APP_RECT clip,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_width,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			ICustomClip *fclip,
			ICustomRender *frender,
			const bool blend)
		{
			// Check buffer and block rect are valid
			if (m_sImage.getWidth() == 0 || !block_rect.IsValid() || block_rect.IsEmpty() || location == graphics::bplInside || location == graphics::bplOutside || color.getAlpha() == 0)
				return;
			// Adjust clip rect
			clip *= {0, 0, (int)m_sImage.getWidth(), (int)m_sImage.getHeight()};
			clip *= block_rect;
			// Vars
			int tx, ty;
			DATA data;
			FillBlockData(data, block_rect.Width(), block_rect.Height(), border_width, border_radius, border_antialiazing, location);
			FClassify classify = SelectClassify(data);
			int x1_from, x1_to, x2_from, x2_to, x3_from, x3_to, y1_from, y1_to, y2_from, y2_to, y3_from, y3_to;
			double clip_alpha;
			SelectBorderRanges(data, block_rect, clip, x1_from, x1_to, x2_from, x2_to, x3_from, x3_to, y1_from, y1_to, y2_from, y2_to, y3_from, y3_to);
			// Rendering
			if (!fclip && !frender)
			{
				for (ty = y1_from; ty < y1_to; ty++)
					for (tx = x1_from; tx < x1_to; tx++)
					{
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						if (blend)
							m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha), 255);
						else
							m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha));
					}
				for (ty = y2_from; ty < y2_to; ty++)
					for (tx = x2_from; tx < x2_to; tx++)
					{
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						if (blend)
							m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha), 255);
						else
							m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha));
					}
				for (ty = y3_from; ty < y3_to; ty++)
					for (tx = x3_from; tx < x3_to; tx++)
					{
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						if (blend)
							m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha), 255);
						else
							m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha));
					}
			}
			else
			{
				for (ty = y1_from; ty < y1_to; ty++)
					for (tx = x1_from; tx < x1_to; tx++)
					{
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						if (fclip && !fclip->Check(tx, ty, location))
							continue;
						if (frender)
							frender->Render(this, tx, ty, { color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha) });
						else
							if (blend)
								m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha), 255);
							else
								m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha));
					}
				for (ty = y2_from; ty < y2_to; ty++)
					for (tx = x2_from; tx < x2_to; tx++)
					{
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						if (fclip && !fclip->Check(tx, ty, location))
							continue;
						if (frender)
							frender->Render(this, tx, ty, { color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha) });
						else
							if (blend)
								m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha), 255);
							else
								m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha));
					}
				for (ty = y3_from; ty < y3_to; ty++)
					for (tx = x3_from; tx < x3_to; tx++)
					{
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						if (fclip && !fclip->Check(tx, ty, location))
							continue;
						if (frender)
							frender->Render(this, tx, ty, { color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha) });
						else
							if (blend)
								m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha), 255);
							else
								m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), (unsigned char)(color.getAlpha() * clip_alpha));
					}
			}
		}
#pragma endregion

#pragma region Free drawing
		void CImageMemory::Draw(
			APP_RECT clip,
			ICustomDraw *fdraw)
		{
			if (!fdraw)
				return;
			clip *= {0, 0, (int)m_sImage.getWidth(), (int)m_sImage.getHeight()};
			int x, y;
			APP_COLOR c;
			for (y = clip.Top; y < clip.Bottom; y++)
				for (x = clip.Left; x < clip.Right; x++)
				{
					c = fdraw->Draw(x, y);
					if (c.getAlpha() > 0)
						m_sImage.BlendPixel(x, y, c, 255);
				}
		}
#pragma endregion

#pragma region Blur
		void CImageMemory::BoxBlur(
			const APP_COLOR &color,
			const int dx,
			const int dy,
			const size_t radius,
			APP_RECT clip,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			IImage::ICustomClip *fclip,
			IImage::ICustomRender *frender,
			const bool blend)
		{
			if (!clip.IsValid() || clip.IsEmpty() || !block_rect.IsValid() || block_rect.IsEmpty())
				return;
			APP_RECT blur_rect{ (int)block_rect.Left + dx - (int)radius, (int)block_rect.Top + dy - (int)radius, (int)block_rect.Right + dx + (int)radius, (int)block_rect.Bottom + dy + (int)radius };
			blur_rect *= {0, 0, (int)m_sImage.getWidth(), (int)m_sImage.getHeight()};
			if (!blur_rect.IsValid() || blur_rect.IsEmpty())
				return;
			clip *= {0, 0, (int)m_sImage.getWidth(), (int)m_sImage.getHeight()};
			clip *= blur_rect;
			m_sBlur.Alloc(m_sImage.getWidth(), m_sImage.getHeight());
			DATA data;
			FillBlockData(data, block_rect.Width(), block_rect.Height(), { 0, 0, 0, 0 }, border_radius, border_antialiazing, graphics::bplInside);
			FClassify classify = SelectClassify(data);
			int tx, ty;
			unsigned char a;
			// Create alpha map of block
			for (ty = blur_rect.Top; ty < blur_rect.Bottom; ty++)
				for (tx = blur_rect.Left; tx < blur_rect.Right; tx++)
				{
					m_sBlur[tx][ty][0] = (unsigned char)(255.0 * classify(tx - (int)block_rect.Left - dx, ty - (int)block_rect.Top - dy, data));
					m_sBlur[tx][ty][2] = (unsigned char)(255.0 * classify(tx - (int)block_rect.Left, ty - (int)block_rect.Top, data));
				}
			m_sBlur.Blur(0, 1, radius, { (size_t)blur_rect.Left, (size_t)blur_rect.Top, (size_t)blur_rect.Right, (size_t)blur_rect.Bottom });
			if (!fclip && !frender)
			{
				for (tx = clip.Left; tx < clip.Right; tx++)
					for (ty = clip.Top; ty < clip.Bottom; ty++)
					{
						a = (unsigned char)(((int)m_sBlur[tx][ty][0] * (int)color.getAlpha() * (255 - (int)m_sBlur[tx][ty][2])) >> 16);
						if (blend)
							m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), a, 255);
						else
							m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), a);
					}
			}
			else
				for (ty = clip.Top; ty < clip.Bottom; ty++)
					for (tx = clip.Left; tx < clip.Right; tx++)
					{
						if (fclip && !fclip->Check(tx, ty, graphics::bplInside))
							continue;
						a = (unsigned char)(((int)m_sBlur[tx][ty][0] * (int)color.getAlpha() * (255 - (int)m_sBlur[tx][ty][2])) >> 16);
						if (frender)
							frender->Render(this, tx, ty, { color.getRed(), color.getGreen(), color.getBlue(), a });
						else
							if (blend)
								m_sImage.BlendPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), a, 255);
							else
								m_sImage.setPixel(tx, ty, color.getRed(), color.getGreen(), color.getBlue(), a);
					}
		}

		void CImageMemory::Blur(
			const APP_COLOR &color,
			const size_t radius,
			const APP_RECT &rect)
		{
			m_sImage.Blur(3, 0, radius, { (size_t)std::max(0, rect.Left), (size_t)std::max(0, rect.Top), (size_t)std::max(0, rect.Right), (size_t)std::max(0, rect.Bottom) });
			size_t x, y;
			for (y = 0; y < m_sImage.getHeight(); y++)
				for (x = 0; x < m_sImage.getWidth(); x++)
				{
					m_sImage[x][y][0] = color[0];
					m_sImage[x][y][1] = color[1];
					m_sImage[x][y][2] = color[2];
					m_sImage[x][y][3] = (unsigned int)((double)color[3] * m_sImage[x][y][3] / 255.0);
				}
		}
#pragma endregion

	#pragma region Gradient
		void CImageMemory::RenderGradient(
			const GRADIENT_TYPE type,
			const size_t point_count,
			const GRADIENT_POINT *points,
			const graphics::BLOCK_POINT_LOCATION location,
			APP_RECT clip,
			const APP_RECT &rect,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_width,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			ICustomClip *fclip,
			ICustomRender *frender,
			const bool blend)
		{
			// Check buffer and block rect are valid
			if (m_sImage.getWidth() == 0 || !block_rect.IsValid() || block_rect.IsEmpty() || !rect.IsValid() || rect.IsEmpty() || point_count < 2 || !points)
				return;
			// Adjust clip rect
			clip *= {0, 0, (int)m_sImage.getWidth(), (int)m_sImage.getHeight()};
			clip *= rect;
			clip *= block_rect;
			// Vars
			int tx, ty;
			double clip_alpha;
			APP_COLOR c;
			DATA data;
			FillBlockData(data, block_rect.Width(), block_rect.Height(), border_width, border_radius, border_antialiazing, location);
			FillGradientData(data, rect, point_count, type, points);
			FClassify classify = SelectClassify(data);
			// Rendering
			if (!fclip && !frender)
				for (ty = clip.Top; ty < clip.Bottom; ty++)
					for (tx = clip.Left; tx < clip.Right; tx++)
					{
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						c = CalculateGradient(tx, ty, data);
						if (blend)
							m_sImage.BlendPixel(tx, ty, c.getRed(), c.getGreen(), c.getBlue(), (unsigned char)(c.getAlpha() * clip_alpha), 255);
						else
							m_sImage.setPixel(tx, ty, c.getRed(), c.getGreen(), c.getBlue(), (unsigned char)(c.getAlpha() * clip_alpha));
					}
			else
				for (ty = clip.Top; ty < clip.Bottom; ty++)
					for (tx = clip.Left; tx < clip.Right; tx++)
					{
						if (fclip && !fclip->Check(tx, ty, location))
							continue;
						if ((clip_alpha = classify(tx - block_rect.Left, ty - block_rect.Top, data)) == 0)
							continue;
						c = CalculateGradient(tx, ty, data);
						if (frender)
							frender->Render(this, tx, ty, { c.getRed(), c.getGreen(), c.getBlue(), (unsigned char)(c.getAlpha() * clip_alpha) });
						else
							if (blend)
								m_sImage.BlendPixel(tx, ty, c.getRed(), c.getGreen(), c.getBlue(), (unsigned char)(c.getAlpha() * clip_alpha), 255);
							else
								m_sImage.setPixel(tx, ty, c.getRed(), c.getGreen(), c.getBlue(), (unsigned char)(c.getAlpha() * clip_alpha));
					}
		}
	#pragma endregion
	}
}