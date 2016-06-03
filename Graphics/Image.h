// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include <algorithm>
#include "..\Math\Rectangle.h"
#include "..\Math\Vector.h"
#include "..\Math\Matrix.h"
#include "Pixel.h"

namespace licui
{
	namespace graphics
	{
		template<class Type, size_t Channels> struct IMAGE;

		template<class Type, size_t Channels> struct BASE_IMAGE
		{
		public:
			struct IMAGE_COLUMN
			{
				friend BASE_IMAGE;
			protected:
				PIXEL<Type, Channels> *m_pData;
			#ifdef _DEBUG
				size_t m_iHeight;
			#endif
			public:
				inline PIXEL<Type, Channels> &operator[](const size_t y);
				inline const PIXEL<Type, Channels> &operator[](const size_t y) const;
			};
		protected:
			size_t m_iWidth;
			size_t m_iHeight;
			PIXEL<Type, Channels> *m_pData;
			IMAGE_COLUMN *m_pColumns;
		public:
			inline size_t getWidth() const;
			inline size_t getHeight() const;
			inline math::RECTANGLE<int> getRect() const;
			inline math::POINT<int> getSize() const;

			inline IMAGE_COLUMN &operator[](const size_t x);
			inline const IMAGE_COLUMN &operator[](const size_t x) const;

			inline BASE_IMAGE();
			inline BASE_IMAGE(const size_t width, const size_t height);
			virtual ~BASE_IMAGE();

			void Alloc(const size_t width, const size_t height);
			void Free();
			void BlendPixel(const size_t x, const size_t y, const PIXEL<Type, Channels> &pixel, const size_t alpha_channel, const Type max);
			void Fill(const PIXEL<Type, Channels> &color);
			void FillChannel(const size_t channel, const Type value);
			void FillRect(math::RECTANGLE<int> rect, const PIXEL<Type, Channels> &pixel);
			void Blur(const size_t channel, const size_t tmp_channel, const size_t radius, math::RECTANGLE<size_t> rect);
			template<class TDraw> void Draw(const math::RECTANGLE<int> &rect, math::MATRIX<float> transform, TDraw draw);
			void Draw(const IMAGE<Type, Channels> &img, const int x, const int y, const size_t alpha_channel, const Type max, const math::RECTANGLE<int> &clip);
		private:
			void BlurBoxes(const double radius, int *values);
			void BlurT4(const size_t channel, const size_t tmp_channel, const size_t radius, math::RECTANGLE<size_t> rect);
			void BlurH4(const size_t channel, const size_t tmp_channel, const size_t radius, math::RECTANGLE<size_t> rect);
			void Blur4(const size_t src_channel, const size_t dst_channel, const size_t radius, math::RECTANGLE<size_t> rect);
		};

		template<class Type, size_t Channels> struct IMAGE :public BASE_IMAGE<Type, Channels>
		{

		};

		template<class Type> struct IMAGE<Type, 3> :public BASE_IMAGE<Type, 3>
		{
			inline void setPixel(const size_t x, const size_t y, const Type r, const Type g, const Type b);
			void Fill(const PIXEL<Type, 3> &color);
			void Fill(const Type r, const Type g, const Type b);
		};

		template<class Type> struct IMAGE<Type, 4> :public BASE_IMAGE<Type, 4>
		{
			inline void setPixel(const size_t x, const size_t y, const Type r, const Type g, const Type b, const Type a);
			void BlendPixel(const size_t x, const size_t y, const PIXEL<Type, 4> &pixel, const Type max);
			void BlendPixel(const size_t x, const size_t y, const Type r, const Type g, const Type b, const Type a, const Type max);
			void Fill(const PIXEL<Type, 4> &color);
			void Fill(const Type r, const Type g, const Type b, const Type a);
		};

	#pragma region BASE_IMAGE
		template<class Type, size_t Channels> PIXEL<Type, Channels> &BASE_IMAGE<Type, Channels>::IMAGE_COLUMN::operator[](const size_t y)
		{
		#ifdef _DEBUG
			if (y >= m_iHeight)
				throw "Column index is out of bounds";
		#endif
			return m_pData[y];
		}

		template<class Type, size_t Channels> const PIXEL<Type, Channels> &BASE_IMAGE<Type, Channels>::IMAGE_COLUMN::operator[](const size_t y) const
		{
		#ifdef _DEBUG
			if (y >= m_iHeight)
				throw "Column index is out of bounds";
		#endif
			return m_pData[y];
		}

		template<class Type, size_t Channels> BASE_IMAGE<Type, Channels>::BASE_IMAGE() : m_iWidth{ 0 }, m_iHeight{ 0 }, m_pColumns{ nullptr }, m_pData{ nullptr }
		{

		}

		template<class Type, size_t Channels> BASE_IMAGE<Type, Channels>::BASE_IMAGE(const size_t width, const size_t height) : m_iWidth{ 0 }, m_iHeight{ 0 }, m_pColumns{ nullptr }, m_pData{ nullptr }
		{
			Alloc(width, height);
		}

		template<class Type, size_t Channels> BASE_IMAGE<Type, Channels>::~BASE_IMAGE()
		{
			Free();
		}

		template<class Type, size_t Channels> typename BASE_IMAGE<Type, Channels>::IMAGE_COLUMN &BASE_IMAGE<Type, Channels>::operator[](const size_t x)
		{
		#ifdef _DEBUG
			if (x >= m_iWidth)
				throw "Row index is out of bounds";
		#endif
			return m_pColumns[x];
		}

		template<class Type, size_t Channels> const typename BASE_IMAGE<Type, Channels>::IMAGE_COLUMN &BASE_IMAGE<Type, Channels>::operator[](const size_t x) const
		{
		#ifdef _DEBUG
			if (x >= m_iWidth)
				throw "Row index is out of bounds";
		#endif
			return m_pColumns[x];
		}

		template<class Type, size_t Channels> size_t BASE_IMAGE<Type, Channels>::getWidth() const
		{
			return m_iWidth;
		}

		template<class Type, size_t Channels> size_t BASE_IMAGE<Type, Channels>::getHeight() const
		{
			return m_iHeight;
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::Alloc(const size_t width, const size_t height)
		{
			if (width != m_iWidth || height != m_iHeight)
			{
				Free();
				if (width > 0 && height > 0)
				{
					m_iWidth = width;
					m_iHeight = height;
					m_pData = new PIXEL<Type, Channels>[width * height];
					m_pColumns = new IMAGE_COLUMN[m_iWidth];
					for (size_t x = 0; x < m_iWidth; x++)
					{
						m_pColumns[x].m_pData = &m_pData[x * m_iHeight];
					#ifdef _DEBUG
						m_pColumns[x].m_iHeight = m_iHeight;
					#endif
					}
				}
			}
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::Free()
		{
			if (m_pData)
			{
				delete[] m_pData;
				delete[] m_pColumns;
				m_pData = nullptr;
				m_pColumns = nullptr;
			}
			m_iWidth = m_iHeight = 0;
		}

		template<class Type, size_t Channels> math::RECTANGLE<int> BASE_IMAGE<Type, Channels>::getRect() const
		{
			return{ 0, 0, (int)m_iWidth, (int)m_iHeight };
		}

		template<class Type, size_t Channels> math::POINT<int> BASE_IMAGE<Type, Channels>::getSize() const
		{
			return{ m_iWidth, m_iHeight };
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::BlendPixel(const size_t x, const size_t y, const PIXEL<Type, Channels> &pixel, const size_t alpha_channel, const Type max)
		{
		#ifdef _DEBUG
			if (x >= m_iWidth)
				throw "x is out of bounds";
			if (y >= m_iHeight)
				throw "y is out of bounds";
			if (alpha_channel >= Channels)
				throw "alpha_channel is out of bounds";
		#endif
			double mix{ (double)pixel[alpha_channel] / max };
			for (unsigned char channel = 0; channel < Channels; channel++)
				if (channel != alpha_channel)
					(*this)[x][y][channel] = (Type)((*this)[x][y][channel] * (1.0 - mix) + pixel[channel] * mix);
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::Fill(const PIXEL<Type, Channels> &color)
		{
			size_t x, y;
			unsigned char channel;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					for (channel = 0; channel < Channels, channel++)
						(*this)[x][y][channel] = color;
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::FillChannel(const size_t channel, const Type value)
		{
		#ifdef _DEBUG
			if (channel >= Channels)
				throw "channel is out of bounds";
		#endif
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y][channel] = value;
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::FillRect(math::RECTANGLE<int> rect, const PIXEL<Type, Channels> &pixel)
		{
			rect *= {0, 0, (int)m_iWidth, (int)m_iHeight};
			int x, y;
			for (y = rect.Top; y < rect.Bottom; y++)
				for (x = rect.Left; x < rect.Right; x++)
					(*this)[x][y] = pixel;
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::BlurBoxes(const double radius, int *values)
		{
			double wideal{ std::sqrt(4.0 * radius * radius + 1.0) };
			int wl{ (int)std::floor(wideal) };
			if (wl % 2 == 0)
				wl--;
			int wu{ wl + 2 };
			double mideal{ (12.0 * radius * radius - 3.0 * wl * wl - 12.0 * wl - 12.0) / (-4.0 * wl - 4.0) };
			int m{ (int)std::round(mideal) };
			values[0] = 0 < m ? wl : wu;
			values[1] = 1 < m ? wl : wu;
			values[2] = 2 < m ? wl : wu;
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::BlurT4(const size_t channel, const size_t tmp_channel, const size_t radius, math::RECTANGLE<size_t> rect)
		{
			double iarr{ 1.0 / (radius + radius + 1.0) };
			size_t j, x, ty, ly, ry, fv, lv, val;
			for (x = rect.Left; x < rect.Right; x++)
			{
				ty = rect.Top;
				ly = rect.Top;
				ry = rect.Top + radius;
				fv = (*this)[x][rect.Top][channel];
				lv = (*this)[x][rect.Bottom - 1][channel];
				val = (radius + 1) * fv;
				for (j = 0; j < radius; j++)
					val += (*this)[x][rect.Top + j][channel];
				for (j = 0; j <= radius; j++)
				{
					val += (*this)[x][ry++][channel] - fv;
					(*this)[x][ty++][tmp_channel] = (Type)std::round(val * iarr);
				}
				for (j = rect.Top + radius + 1; j < rect.Bottom - radius; j++)
				{
					val += (*this)[x][ry++][channel] - (*this)[x][ly++][channel];
					(*this)[x][ty++][tmp_channel] = (Type)std::round(val * iarr);
				}
				for (j = rect.Bottom - radius; j < rect.Bottom; j++)
				{
					val += lv - (*this)[x][ly++][channel];
					(*this)[x][ty++][tmp_channel] = (Type)(val * iarr);
				}
			}
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::BlurH4(const size_t channel, const size_t tmp_channel, const size_t radius, math::RECTANGLE<size_t> rect)
		{
			double iarr{ 1.0 / (radius + radius + 1.0) };
			size_t j, y, tx, lx, rx, fv, lv, val;
			for (y = rect.Top; y < rect.Bottom; y++)
			{
				tx = rect.Left;
				lx = rect.Left;
				rx = rect.Left + radius;
				fv = (*this)[rect.Left][y][channel];
				lv = (*this)[rect.Right - 1][y][channel];
				val = (radius + 1) * fv;
				for (j = 0; j < radius; j++)
					val += (*this)[rect.Left + j][y][channel];
				for (j = 0; j <= radius; j++)
				{
					val += (*this)[rx++][y][channel] - fv;
					(*this)[tx++][y][tmp_channel] = (Type)std::round(val * iarr);
				}
				for (j = rect.Left + radius + 1; j < rect.Right - radius; j++)
				{
					val += (*this)[rx++][y][channel] - (int)(*this)[lx++][y][channel];
					(*this)[tx++][y][tmp_channel] = (Type)std::round(val * iarr);
				}
				for (j = rect.Right - radius; j < rect.Right; j++)
				{
					val += lv - (int)((*this)[lx++][y][channel]);
					(*this)[tx++][y][tmp_channel] = (Type)(val * iarr);
				}
			}
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::Blur4(const size_t channel, const size_t tmp_channel, const size_t radius, math::RECTANGLE<size_t> rect)
		{
			BlurH4(channel, tmp_channel, radius, rect);
			BlurT4(tmp_channel, channel, radius, rect);
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::Blur(const size_t channel, const size_t tmp_channel, const size_t radius, math::RECTANGLE<size_t> rect)
		{
		#ifdef _DEBUG
			if (channel >= Channels)
				throw "channel is out of bounds";
			if (tmp_channel >= Channels)
				throw "tmp_channel is out of bound";
			if (channel == tmp_channel)
				throw "channels are same";
		#endif
			int boxes[3];
			BlurBoxes(radius * 0.5, boxes);
			Blur4(channel, tmp_channel, (boxes[0] - 1) / 2, rect);
			Blur4(channel, tmp_channel, (boxes[1] - 1) / 2, rect);
			Blur4(channel, tmp_channel, (boxes[2] - 1) / 2, rect);
		}

		template<class Type, size_t Channels> template<class TDraw> void BASE_IMAGE<Type, Channels>::Draw(const math::RECTANGLE<int> &rect, math::MATRIX<float> transform, TDraw draw)
		{
			int x, y;
			VECTOR<float> v{ 0, 0, 1 }, t;
			transform.Inverse();
			for (y = rect.Top; y < rect.Bottom; y++)
			{
				v[1] = (float)y;
				for (x = rect.Left; x < rect.Right; x++)
				{
					v[0] = (float)x;
					t = v * transform;
					draw(x, y, t[0], t[1]);
				}
			}
		}

		template<class Type, size_t Channels> void BASE_IMAGE<Type, Channels>::Draw(const IMAGE<Type, Channels> &img, const int x, const int y, const size_t alpha_channel, const Type max, const math::RECTANGLE<int> &clip)
		{
			math::RECTANGLE<int> r{ 0, 0, (int)m_iWidth, (int)m_iHeight }, ri{ x, y, x + (int)img.getWidth(), y + (int)img.getHeight() };
			r *= clip;
			r *= ri;
			int tx, ty;
			for (ty = r.Top; ty < r.Bottom; ty++)
				for (tx = r.Left; tx < r.Right; tx++)
					BlendPixel(tx, ty, img[tx - x][ty - y], alpha_channel, max);
		}
	#pragma endregion

	#pragma region IMAGE<Type, 3>
		template<class Type> void IMAGE<Type, 3>::setPixel(const size_t x, const size_t y, const Type r, const Type g, const Type b)
		{
		#ifdef _DEBUG
			if (x >= m_iWidth)
				throw "x is out of bounds";
			if (y >= m_iHeight)
				throw "y is out of bounds";
		#endif
			(*this)[x][y].setRed(r);
			(*this)[x][y].setGreen(g);
			(*this)[x][y].setBlue(b);
		}

		template<class Type> void IMAGE<Type, 3>::Fill(const PIXEL<Type, 3> &color)
		{
			size_t x, y;
			unsigned char channel;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] = color;
		}

		template<class Type> void IMAGE<Type, 3>::Fill(const Type r, const Type g, const Type b)
		{
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y].setPixel(r, g, b);
		}
	#pragma endregion

	#pragma region IMAGE<Type, 4>
		template<class Type> void IMAGE<Type, 4>::setPixel(const size_t x, const size_t y, const Type r, const Type g, const Type b, const Type a)
		{
		#ifdef _DEBUG
			if (x >= m_iWidth)
				throw "x is out of bounds";
			if (y >= m_iHeight)
				throw "y is out of bounds";
		#endif
			(*this)[x][y].setRed(r);
			(*this)[x][y].setGreen(g);
			(*this)[x][y].setBlue(b);
			(*this)[x][y].setAlpha(a);
		}

		template<class Type> void IMAGE<Type, 4>::BlendPixel(const size_t x, const size_t y, const PIXEL<Type, 4> &pixel, const Type max)
		{
		#ifdef _DEBUG
			if (x >= m_iWidth)
				throw "x is out of bounds";
			if (y >= m_iHeight)
				throw "y is out of bounds";
		#endif
			double mix{ (double)pixel.getAlpha() / max };
			for (unsigned char channel = 0; channel < 3; channel++)
				(*this)[x][y][channel] = (Type)((*this)[x][y][channel] * (1.0 - mix) + pixel[channel] * mix);
		}

		template<class Type> void IMAGE<Type, 4>::BlendPixel(const size_t x, const size_t y, const Type r, const Type g, const Type b, const Type a, const Type max)
		{
		#ifdef _DEBUG
			if (x >= m_iWidth)
				throw "x is out of bounds";
			if (y >= m_iHeight)
				throw "y is out of bounds";
		#endif
			double mix{ (double)a / max };
			(*this)[x][y].setRed((Type)((*this)[x][y].getRed() * (1.0 - mix) + r * mix));
			(*this)[x][y].setGreen((Type)((*this)[x][y].getGreen() * (1.0 - mix) + g * mix));
			(*this)[x][y].setBlue((Type)((*this)[x][y].getBlue() * (1.0 - mix) + b * mix));
		}

		template<class Type> void IMAGE<Type, 4>::Fill(const PIXEL<Type, 4> &color)
		{
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] = color;
		}

		template<class Type> void IMAGE<Type, 4>::Fill(const Type r, const Type g, const Type b, const Type a)
		{
			size_t x, y;
			for (y = 0; y < m_iHeight; y++)
				for (x = 0; x < m_iWidth; x++)
					(*this)[x][y] = { r, g, b, a };
		}
	#pragma endregion
	}
}