// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Strings\Strings.h"
#include "Types.h"
#include "Font.h"
#include "Image.h"

namespace licui
{
	namespace application
	{
		class IPresenter
		{
		protected:
			IWindow *m_pWindow;
		public:
			IWindow *getWindow();
			virtual size_t getFontCount() = 0;
			virtual IFont *getFont(const size_t index) = 0;
			virtual size_t getImageFormatCount() const = 0;
			virtual IImage::FORMAT getImageFormat(const size_t index) = 0;
			virtual bool getIsImageFormatSupported(const IImage::FORMAT &format) = 0;

			virtual IPresenter *setWindow(IWindow *value) = 0;

			IPresenter(IWindow *window);

			virtual IFont *FontCreate(CFontData *data) = 0;
			virtual void FontDelete(const size_t index) = 0;
			virtual void FontDelete(IFont *font) = 0;

			virtual void Present(const APP_RECT *clip = nullptr) = 0;
			virtual bool ValidateBufferSize() = 0;

			virtual IImage *ImageCreate(const size_t width, const size_t height, const String &name, IImage *old, const IImage::FORMAT &format) = 0;
			virtual IImage *ImageCreate(const APP_IMAGE &data, const String &name, IImage *old, const IImage::FORMAT &format) = 0;
			virtual void ImageFree(IImage *image) = 0;

			virtual void RenderString(
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
				const bool draw_text,
				const bool draw_shadow,
				const APP_COLOR &text_color,
				const APP_COLOR &shadow_color,
				IImage::ICustomClip *fclip,
				IImage::ICustomRender *frender,
				const bool blend) = 0;

			virtual void RenderImage(
				IImage *image,
				const APP_RECT &image_part,
				const double x,
				const double y,
				const double angle,
				const double sx,
				const double sy,
				const bool repeat_x,
				const bool repeat_y,
				const bool interpolate,
				const APP_RECT &clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				const graphics::BLOCK_POINT_LOCATION location,
				IImage::ICustomClip *fclip,
				IImage::ICustomRender *frender,
				const bool blend) = 0;

			virtual void FillRect(
				const APP_COLOR &color,
				const APP_RECT &clip,
				const APP_RECT &rect,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				const graphics::BLOCK_POINT_LOCATION location,
				IImage::ICustomClip *fclip,
				IImage::ICustomRender *frender,
				const bool blend) = 0;

			virtual void MultiFillRect(
				const APP_COLOR colors[graphics::bplBottom + 1],
				const APP_RECT &clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				IImage::ICustomClip *fclip,
				IImage::ICustomRender *frender,
				const bool blend) = 0;

			virtual void RenderBorder(
				const graphics::BLOCK_POINT_LOCATION location,
				const APP_COLOR &color,
				const APP_RECT &clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				IImage::ICustomClip *fclip,
				IImage::ICustomRender *frender,
				const bool blend) = 0;

			virtual void Draw(
				const APP_RECT &clip,
				IImage::ICustomDraw *fdraw) = 0;

			virtual void BoxBlur(
				const APP_COLOR &color,
				const int dx,
				const int dy,
				const size_t radius,
				const APP_RECT &clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				IImage::ICustomClip *fclip,
				IImage::ICustomRender *frender,
				const bool blend) = 0;

			virtual void RenderGradient(
				const IImage::GRADIENT_TYPE type,
				const size_t point_count,
				const IImage::GRADIENT_POINT *points,
				const graphics::BLOCK_POINT_LOCATION location,
				const APP_RECT &clip,
				const APP_RECT &rect,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				IImage::ICustomClip *fclip,
				IImage::ICustomRender *frender,
				const bool blend) = 0;
		};
	}
}