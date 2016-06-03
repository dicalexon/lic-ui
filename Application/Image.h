// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Strings\Strings.h"
#include "..\Graphics\Pixel.h"
#include "Types.h"

namespace licui
{
	namespace application
	{
		class IImage
		{
		public:
			class ICustomClip
			{
			public:
				virtual double Check(const int x, const int y, const graphics::BLOCK_POINT_LOCATION location) = 0;
			};

			class ICustomRender
			{
			public:
				virtual void Render(IImage *dest, const int x, const int y, const APP_COLOR &color) = 0;
			};

			class ICustomDraw
			{
			public:
				virtual APP_COLOR Draw(const int x, const int y) = 0;
			};

			struct FORMAT
			{
			private:
				char Data[4];
			public:
				inline FORMAT();
				inline FORMAT(const AnsiString &value);

				inline bool operator==(const AnsiString &cmp) const;
				inline bool operator!=(const AnsiString &cmp) const;
				inline bool operator==(const FORMAT &other) const;
				inline bool operator!=(const FORMAT &other) const;
				inline operator AnsiString() const;
			};

			struct LOCK
			{
				size_t X;
				size_t Y;
				size_t Width;
				size_t Height;
				size_t Pitch;
				void *Data;
				FORMAT Format;
			};

			enum GRADIENT_TYPE
			{
				gtHorizontal,
				gtVertical,
				gtRadial,
				gtDiagonalDown, // From left-top to right-bottom
				gtDiagonalUp // From left-bottom to right-top
			};

			struct GRADIENT_POINT
			{
				double Position; // Position in percents
				APP_COLOR Color;
			};

			struct GRADIENT
			{
				GRADIENT_TYPE GradientType;
				size_t GradientPointCount;
				GRADIENT_POINT *GradientPoints;
				bool GradientPointsSorted;

				inline void setGradientPointCount(const size_t count);

				inline GRADIENT();
				inline ~GRADIENT();

				inline void SortGradientPoints();
			};
		private:
			struct COLUMN
			{
			private:
				IImage *m_pImage;
				const size_t m_iX;
			public:
				inline COLUMN(IImage *image, const size_t x);

				inline APP_COLOR &operator[](const size_t y);
			};

			struct COLUMN_CONST
			{
			private:
				const IImage *m_pImage;
				const size_t m_iX;
			public:
				inline COLUMN_CONST(const IImage *image, const size_t x);

				inline const APP_COLOR &operator[](const size_t y) const;
			};
		public:
			inline COLUMN operator[](const size_t x);
			inline const COLUMN_CONST operator[](const size_t x) const;

			virtual size_t getWidth() const = 0;
			virtual size_t getHeight() const = 0;
			virtual String getName() const = 0;
			virtual FORMAT getFormat() const = 0;
			virtual APP_COLOR &getPixel(const size_t x, const size_t y) = 0;
			virtual const APP_COLOR &getPixel(const size_t x, const size_t y) const = 0;
			virtual bool getIsValid() const = 0;

			virtual void setPixel(const size_t x, const size_t y, const APP_COLOR &value) = 0;
			virtual void setPixel(const size_t x, const size_t y, const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) = 0;

			virtual void BlendPixel(const size_t x, const size_t y, const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) = 0;
			virtual void BlendPixel(const size_t x, const size_t y, const APP_COLOR &color) = 0;

			virtual LOCK *Lock(const size_t x, const size_t y, const size_t width, const size_t height, const FORMAT &format = { "RGBA" }) = 0;
			virtual void Unlock(LOCK *lock) = 0;
			virtual void Release() = 0;
			virtual bool BeginPaint() = 0;
			virtual void EndPaint() = 0;
			virtual void Clear(const APP_COLOR &value) = 0;

			virtual void RenderString(
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
				const bool blend) = 0;

			virtual void RenderImage(
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
				const bool blend) = 0;

			virtual void FillRect(
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
				const bool blend) = 0;

			virtual void MultiFillRect(
				const APP_COLOR colors[graphics::bplBottom + 1],
				APP_RECT clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				ICustomClip *fclip,
				ICustomRender *frender,
				const bool blend) = 0;

			virtual void Draw(
				APP_RECT clip,
				ICustomDraw *fdraw) = 0;

			virtual void BoxBlur(
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
				const bool blend) = 0;

			virtual void Blur(
				const APP_COLOR &color,
				const size_t radius,
				const APP_RECT &rect) = 0;

			virtual void RenderBorder(
				const graphics::BLOCK_POINT_LOCATION location,
				const APP_COLOR &color,
				APP_RECT clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				ICustomClip *fclip,
				ICustomRender *frender,
				const bool blend) = 0;

			virtual void RenderGradient(
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
				const bool blend) = 0;
		};

#pragma region Implementation
#pragma region FORMAT
		IImage::FORMAT::FORMAT():
			Data{ 0, 0, 0, 0 }
		{

		}

		IImage::FORMAT::FORMAT(const AnsiString &value)
		{
			if (value.length() >= 4)
			{
				Data[0] = value[0];
				Data[1] = value[1];
				Data[2] = value[2];
				Data[3] = value[3];
			}
			else
				Data[0] = Data[1] = Data[2] = Data[3] = 0;
		}

		bool IImage::FORMAT::operator==(const AnsiString &cmp) const
		{
			return cmp.length() == 4 && cmp[0] == Data[0] && cmp[1] == Data[1] && cmp[2] == Data[2] && cmp[3] == Data[3];
		}

		bool IImage::FORMAT::operator!=(const AnsiString &cmp) const
		{
			return cmp.length() != 4 || cmp[0] != Data[0] || cmp[1] != Data[1] || cmp[2] != Data[2] || cmp[3] != Data[3];
		}

		bool IImage::FORMAT::operator==(const FORMAT &other) const
		{
			return other.Data[0] == Data[0] && other.Data[1] == Data[1] && other.Data[2] == Data[2] && other.Data[3] == Data[3];
		}

		bool IImage::FORMAT::operator!=(const FORMAT &other) const
		{
			return other.Data[0] != Data[0] || other.Data[1] != Data[1] || other.Data[2] != Data[2] || other.Data[3] != Data[3];
		}

		IImage::FORMAT::operator AnsiString() const
		{
			AnsiString result;
			result.push_back(Data[0]);
			result.push_back(Data[1]);
			result.push_back(Data[2]);
			result.push_back(Data[3]);
			return result;
		}
#pragma endregion

#pragma region COLUMN
		IImage::COLUMN::COLUMN(IImage *image, const size_t x) : m_pImage{ image }, m_iX{ x }
		{

		}

		APP_COLOR &IImage::COLUMN::operator[](const size_t y)
		{
			return m_pImage->getPixel(m_iX, y);
		}
#pragma endregion

#pragma region COLUMN_CONST
		IImage::COLUMN_CONST::COLUMN_CONST(const IImage *image, const size_t x) : m_pImage{ image }, m_iX{ x }
		{
		
		}

		const APP_COLOR &IImage::COLUMN_CONST::operator[](const size_t y) const
		{
			return m_pImage->getPixel(m_iX, y);
		}
#pragma endregion

#pragma region IImage
		IImage::COLUMN IImage::operator[](const size_t x)
		{
			return COLUMN{ this, x };
		}

		const IImage::COLUMN_CONST IImage::operator[](const size_t x) const
		{
			return COLUMN_CONST{ this, x };
		}
#pragma endregion

	#pragma region GRADIENT
		IImage::GRADIENT::GRADIENT():
			GradientType{ gtHorizontal },
			GradientPointCount{ 0 },
			GradientPoints{ nullptr },
			GradientPointsSorted{ true }
		{
		}

		IImage::GRADIENT::~GRADIENT()
		{
			setGradientPointCount(0);
		}

		void IImage::GRADIENT::setGradientPointCount(const size_t count)
		{
			if (count != GradientPointCount)
			{
				if (GradientPoints)
				{
					delete[] GradientPoints;
					GradientPoints = nullptr;
					GradientPointCount = 0;
					GradientPointsSorted = true;
				}
				if (count >= 2)
				{
					GradientPointCount = count;
					GradientPoints = new IImage::GRADIENT_POINT[count];
					GradientPointsSorted = false;
					for (size_t i = 0; i < count; i++)
						GradientPoints[i] = { (double)i / ((double)count - 1.0), {0, 0, 0, 0} };
				}
			}
		}

		void IImage::GRADIENT::SortGradientPoints()
		{
			if (!GradientPointsSorted)
			{
				if (GradientPointCount > 1 && GradientPoints)
					std::qsort(GradientPoints, GradientPointCount, sizeof(GRADIENT_POINT), [](const void *a, const void *b) {
					if (((GRADIENT_POINT*)a)->Position < ((GRADIENT_POINT*)b)->Position)
						return -1;
					if (((GRADIENT_POINT*)a)->Position >((GRADIENT_POINT*)b)->Position)
						return 1;
					return 0;
				});
				GradientPointsSorted = true;
			}
		}
	#pragma endregion
#pragma endregion
	}
}