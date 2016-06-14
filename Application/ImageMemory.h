// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Strings\Strings.h"
#include "Types.h"
#include "Image.h"

namespace licui
{
	namespace application
	{
		class CImageMemory :public IImage
		{
		private:
			struct DATA
			{
				int Width;
				int Height;
				APP_RECT Border;
				APP_RECT Radius;
				size_t AntiAliazing;
				double Locations[graphics::bplBottom + 1];
				graphics::BLOCK_POINT_LOCATION Location;
				size_t TextAntialiazing;
				IFont *TextFont;
				const String *Text;
				size_t TextChannel;
				APP_MATRIX Matrix;
				APP_IMAGE *Image;
				APP_RECT ImagePart;
				int ImageX;
				int ImageY;
				bool ImageRepeatX;
				bool ImageRepeatY;
				size_t i;
				size_t j;
				double *alpha;
				size_t alpha_size;

				APP_RECT GradientRect;
				size_t GradientPointCount;
				GRADIENT_TYPE GradientType;
				const GRADIENT_POINT *GradientPoints;

				DATA();
				~DATA();

				void AllocAlpha(const size_t size);
				void ClearAlpha();
				double getAlpha(const size_t x, const size_t y)
				{
					return alpha[y * alpha_size + x];
				}
				void setAlpha(const size_t x, const size_t y, const double value)
				{
					alpha[y * alpha_size + x] = value;
				}
			};

			APP_IMAGE m_sImage;
			graphics::IMAGE<unsigned char, 3> m_sBlur;
			String m_sName;

			typedef double(*FClassify)(const int x, const int y, DATA &data);
			typedef double(*FGetAlpha)(const int x, const int y, DATA &data);
			typedef APP_COLOR(*FGetPixel)(const int x, const int y, DATA &data);

			void FillBlockData(DATA &data, const size_t width, const size_t height, const math::RECTANGLE<size_t> &border, const math::RECTANGLE<size_t> &radius, const size_t antialiazing, const graphics::BLOCK_POINT_LOCATION location);
			void FillTextData(DATA &data, const size_t antialiazing, IFont *font, const String *text, const size_t channel, APP_MATRIX &matrix);
			void FillImageData(DATA &data, IImage *image, const APP_RECT &image_part, const int x, const int y, const bool repeat_x, const bool repeat_y);
			void FillGradientData(DATA &data, const APP_RECT &rect, const size_t point_count, const GRADIENT_TYPE type, const GRADIENT_POINT *points);
			FClassify SelectClassify(const DATA &data);
			FGetAlpha SelectTextGetAlpha(DATA &data, const double angle);
			APP_MATRIX CreateTransformation(const double x1, const double y1, const double angle, const double sx, const double sy, const double x2, const double y2);
			FGetPixel SelectGetPixel(DATA &data, const double angle, const double sx, const double sy, const bool interpolate);
			void InternalRenderString(
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
				const bool blend);
			void SelectBorderRanges(const DATA &data, const APP_RECT &block_rect, const APP_RECT &clip, int &x1_from, int &x1_to, int &x2_from, int &x2_to, int &x3_from, int &x3_to, int &y1_from, int &y1_to, int &y2_from, int &y2_to, int &y3_from, int &y3_to);
			APP_COLOR CalculateGradient(const int x, const int y, DATA &data);
		public:
			size_t getWidth() const override;
			size_t getHeight() const override;
			String getName() const override;
			FORMAT getFormat() const override;
			APP_COLOR &getPixel(const size_t x, const size_t y) override;
			const APP_COLOR &getPixel(const size_t x, const size_t y) const override;
			bool getIsValid() const override;
			void setPixel(const size_t x, const size_t y, const APP_COLOR &value) override;
			void setPixel(const size_t x, const size_t y, const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) override;
			void BlendPixel(const size_t x, const size_t y, const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) override;
			void BlendPixel(const size_t x, const size_t y, const APP_COLOR &color) override;
			LOCK *Lock(const size_t x, const size_t y, const size_t width, const size_t height, const FORMAT &format = { "RGBA" }) override;
			void Unlock(LOCK *lock) override;
			void Release() override;
			bool BeginPaint() override;
			void EndPaint() override;
			void Clear(const APP_COLOR &value) override;

			void RenderString(
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
				const bool blend) override;

			void RenderImage(
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
				const bool blend) override;

			void FillRect(
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
				const bool blend) override;

			void MultiFillRect(
				const APP_COLOR colors[graphics::bplBottom + 1],
				APP_RECT clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				ICustomClip *fclip,
				ICustomRender *frender,
				const bool blend) override;

			void Draw(
				APP_RECT clip,
				ICustomDraw *fdraw) override;

			void BoxBlur(
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
				const bool blend) override;

			void Blur(
				const APP_COLOR &color,
				const size_t radius,
				const APP_RECT &rect) override;

			void RenderBorder(
				const graphics::BLOCK_POINT_LOCATION location,
				const APP_COLOR &color,
				APP_RECT clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				ICustomClip *fclip,
				ICustomRender *frender,
				const bool blend) override;

			void RenderGradient(
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
				const bool blend) override;

			CImageMemory();
			CImageMemory(const size_t width, const size_t height, const String &name);

			graphics::IMAGE<unsigned char, 4> &getImage();
			void Alloc(const size_t width, const size_t height);
		};
	}
}