// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include <vector>
#include "..\..\..\Strings\Strings.h"
#include "..\..\Types.h"
#include "..\..\Font.h"
#include "..\..\Presenter.h"
#include "..\..\ImageMemory.h"
#include <Windows.h>

namespace licui
{
	namespace application
	{
		class CPresenterGDI;

		class CFont :public IFont
		{
		private:
			struct CHAR_IMAGE
			{
				wchar_t Char;
				GLYPH Data;
			};
		private:
			HFONT m_hFont;
			std::vector<CHAR_IMAGE*> m_aChars;
			bool m_bIsCharsSorted;
			CHAR_IMAGE m_sSearchChar;
			CPresenterGDI *m_pPresenter;

			void ClearChars();
			void SortChars();
			int FindCharIndex(const wchar_t chr);
			void Recreate();
			CHAR_IMAGE *CreateChar(const wchar_t chr);
		public:
			bool getIsValid() const;

			CFont(CPresenterGDI *presenter, CFontData *data);
			virtual ~CFont();

			virtual GLYPH *getChar(const wchar_t chr);
			virtual APP_POINT getStringSize(const String &str);

			IFont *setName(const String &value) override;
			IFont *setHeight(const int value) override;
			IFont *setWeight(const int value) override;
			IFont *setItalic(const bool value) override;
			IFont *setUnderline(const bool value) override;
			IFont *setStrikeOut(const bool value) override;
			IFont *setWidth(const int value) override;
			IFont *setCharSet(const unsigned int value) override;
			IFont *setQuality(const unsigned int value) override;
			IFont *setPitchAndFamily(const unsigned int value) override;
			IFont *setOrientation(const int value) override;
			IFont *setDistance(const int value) override;
			IFont *setShadow(const bool value) override;
			IFont *setShadowShift(const APP_POINT &value) override;
			IFont *setShadowShift(const int x, const int y) override;
			IFont *setShadowShiftX(const int value) override;
			IFont *setShadowShiftY(const int value) override;
			IFont *setShadowBlur(const size_t value) override;
			IFont *setShadowColor(const APP_COLOR &value) override;
			IFont *setShadowColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) override;
			IFont *setColor(const APP_COLOR &value) override;
			IFont *setColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) override;
			IFont *setInterpolate(const bool value) override;

			void AddCharacters(const String &str) override;
		};

		class CPresenterGDI :public IPresenter
		{
		private:
			HDC m_hDC;
			HBITMAP m_hBitmap;
			size_t m_iBitmapWidth;
			size_t m_iBitmapHeight;
			unsigned char *m_aBuffer;
			std::vector<CFont*> m_aFonts;
			CImageMemory m_sBuffer;
		public:
			HDC getDC();

			size_t getFontCount() override;
			IFont *getFont(const size_t index) override;
			size_t getImageFormatCount() const override;
			IImage::FORMAT getImageFormat(const size_t index) override;
			bool getIsImageFormatSupported(const IImage::FORMAT &format) override;

			IPresenter *setWindow(IWindow *window) override;

			CPresenterGDI(IWindow *window);
			~CPresenterGDI();

			IFont *FontCreate(CFontData *data) override;
			void FontDelete(const size_t index) override;
			void FontDelete(IFont *font) override;

			void Present(const APP_RECT *clip = nullptr) override;
			bool ValidateBufferSize() override;

			IImage *ImageCreate(const size_t width, const size_t height, const String &name, IImage *old, const IImage::FORMAT &format) override;
			IImage *ImageCreate(const APP_IMAGE &data, const String &name, IImage *old, const IImage::FORMAT &format) override;
			void ImageFree(IImage *image) override;

			void RenderString(
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
				const bool blend) override;

			void RenderImage(
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
				const bool blend) override;

			void FillRect(
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
				const bool blend) override;

			void MultiFillRect(
				const APP_COLOR colors[graphics::bplBottom + 1],
				const APP_RECT &clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				IImage::ICustomClip *fclip,
				IImage::ICustomRender *frender,
				const bool blend) override;

			void RenderBorder(
				const graphics::BLOCK_POINT_LOCATION location,
				const APP_COLOR &color,
				const APP_RECT &clip,
				const APP_RECT &block_rect,
				const math::RECTANGLE<size_t> &border_width,
				const math::RECTANGLE<size_t> &border_radius,
				const size_t border_antialiazing,
				IImage::ICustomClip *fclip,
				IImage::ICustomRender *frender,
				const bool blend) override;

			void Draw(
				const APP_RECT &clip,
				IImage::ICustomDraw *fdraw) override;

			void BoxBlur(
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
				const bool blend) override;

			void RenderGradient(
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
				const bool blend) override;
		};
	}
}