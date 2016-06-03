// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "CPresenterGDI.h"
#include "..\..\..\Math\Consts.h"
#include "..\..\Window.h"

namespace licui
{
	namespace application
	{
#pragma region Constructors and destructor
		CPresenterGDI::CPresenterGDI(IWindow *window) :
			IPresenter(window),
			m_hDC{ 0 },
			m_hBitmap{ 0 },
			m_iBitmapWidth{ 0 },
			m_iBitmapHeight{ 0 },
			m_aBuffer{ nullptr }
		{
			
		}

		CPresenterGDI::~CPresenterGDI()
		{
			for (auto pos = m_aFonts.begin(); pos != m_aFonts.end(); pos++)
				delete (*pos);
			if (m_hBitmap)
				DeleteObject(m_hBitmap);
			if (m_hDC)
				DeleteDC(m_hDC);
			if (m_aBuffer)
				delete[] m_aBuffer;
		}
#pragma endregion

#pragma region Getters
		size_t CPresenterGDI::getFontCount()
		{
			return m_aFonts.size();
		}

		IFont *CPresenterGDI::getFont(const size_t index)
		{
			if (index < m_aFonts.size())
				return m_aFonts[index];
			return nullptr;
		}

		HDC CPresenterGDI::getDC()
		{
			if (!m_hDC && m_pWindow && m_pWindow->getIsCreated())
			{
				HDC wdc = GetDC((HWND)m_pWindow->getHandle());
				if (wdc)
				{
					m_hDC = CreateCompatibleDC(wdc);
					ReleaseDC((HWND)m_pWindow->getHandle(), wdc);
				}
			}
			return m_hDC;
		}

		size_t CPresenterGDI::getImageFormatCount() const
		{
			return 1;
		}

		IImage::FORMAT CPresenterGDI::getImageFormat(const size_t index)
		{
			return{ "RGBA" };
		}

		bool CPresenterGDI::getIsImageFormatSupported(const IImage::FORMAT &format)
		{
			return format == "RGBA";
		}
#pragma endregion

#pragma region Setters
		IPresenter *CPresenterGDI::setWindow(IWindow *window)
		{
			if (window != m_pWindow)
			{
				// Remove bitmap
				if (m_hBitmap)
				{
					DeleteObject(m_hBitmap);
					m_hBitmap = 0;
				}
				// Remove DC
				if (m_hDC)
				{
					DeleteDC(m_hDC);
					m_hDC = 0;
				}
				// Set new window and create new DC
				m_pWindow = window;
			}
			return this;
		}
#pragma endregion

#pragma region Fonts
		IFont *CPresenterGDI::FontCreate(CFontData *data)
		{
			m_aFonts.push_back(new CFont(this, data));
			return m_aFonts[m_aFonts.size() - 1];
		}

		void CPresenterGDI::FontDelete(const size_t index)
		{
			if (index < m_aFonts.size())
			{
				delete (m_aFonts[index]);
				m_aFonts.erase(m_aFonts.begin() + index);
			}
		}

		void CPresenterGDI::FontDelete(IFont *font)
		{
			for (auto pos = m_aFonts.begin(); pos != m_aFonts.end(); pos++)
				if ((*pos) == font)
				{
					delete (*pos);
					m_aFonts.erase(pos);
					break;
				}
		}
#pragma endregion

#pragma region Images
		IImage *CPresenterGDI::ImageCreate(const size_t width, const size_t height, const String &name, IImage *old, const IImage::FORMAT &format)
		{
			if (width > 0 && height > 0 && format == "RGBA")
			{
				if (old)
					((CImageMemory*)old)->Alloc(width, height);
				else
					old = (IImage*)(new CImageMemory(width, height, name));
				return old;
			}
			return nullptr;
		}

		IImage *CPresenterGDI::ImageCreate(const APP_IMAGE &data, const String &name, IImage *old, const IImage::FORMAT &format)
		{
			if (format == "RGBA")
			{
				if (old)
					((CImageMemory*)old)->Alloc(data.getWidth(), data.getHeight());
				else
					old = (IImage*)(new CImageMemory(data.getWidth(), data.getHeight(), name));
				size_t x, y;
				APP_IMAGE &img = ((CImageMemory*)old)->getImage();
				for (y = 0; y < data.getHeight(); y++)
					for (x = 0; x < data.getWidth(); x++)
						img[x][y] = data[x][y];
				return old;
			}
			return nullptr;
		}

		void CPresenterGDI::ImageFree(IImage *image)
		{
			if (image)
				delete (CImageMemory*)image;
		}
#pragma endregion

#pragma region Present
		bool CPresenterGDI::ValidateBufferSize()
		{
			if (!m_pWindow)
				return true;
			APP_RECT r = m_pWindow->getClientRect();
			if (!r.IsValid() || r.IsEmpty())
				return true;
			if (m_sBuffer.getWidth() != r.Width() || m_sBuffer.getHeight() != r.Height())
			{
				m_sBuffer.Alloc(r.Width(), r.Height());
				return false;
			}
			return true;
		}

		void CPresenterGDI::Present(const APP_RECT *clip)
		{
			ValidateBufferSize();
			if (!m_pWindow || !m_pWindow->getIsCreated())
				return;
			if (!getDC())
				return;
			if (clip && (!clip->IsValid() || clip->IsEmpty()))
				return;
			// Get window DC
			HDC dc = GetDC((HWND)m_pWindow->getHandle());
			if (!dc)
				return;
			size_t pitch = ((m_sBuffer.getWidth() * 3 + sizeof(DWORD) - 1) / sizeof(DWORD)) * sizeof(DWORD);
			// Recreate bitmap if needed
			if (!m_hBitmap || m_iBitmapWidth != m_sBuffer.getWidth() || m_iBitmapHeight != m_sBuffer.getHeight())
			{
				if (m_hBitmap)
					DeleteObject(m_hBitmap);
				m_hBitmap = CreateCompatibleBitmap(dc, m_sBuffer.getWidth(), m_sBuffer.getHeight());
				m_iBitmapWidth = m_sBuffer.getWidth();
				m_iBitmapHeight = m_sBuffer.getHeight();
				if (m_aBuffer)
					delete[]m_aBuffer;
				m_aBuffer = new unsigned char[((m_sBuffer.getWidth() * 3 + sizeof(DWORD) - 1) / sizeof(DWORD)) * sizeof(DWORD) * m_sBuffer.getHeight()];
			}
			if (!m_hBitmap)
				return;
			// Fill bitmap with data
			APP_RECT rect_full{ 0, 0, (int)m_sBuffer.getWidth(), (int)m_sBuffer.getHeight() };
			if (!clip)
				clip = &rect_full;
			size_t x, y;
			unsigned char *scanline;
			APP_COLOR pixel;
			graphics::IMAGE<unsigned char, 4> &img{ m_sBuffer.getImage() };
			for (y = 0; y < (size_t)clip->Height(); y++)
			{
				scanline = &m_aBuffer[pitch * (clip->Height() - y - 1)];
				for (x = 0; x < img.getWidth(); x++)
				{
					pixel = img[x][y + clip->Top];
					scanline[x * 3 + 0] = pixel.getBlue();
					scanline[x * 3 + 1] = pixel.getGreen();
					scanline[x * 3 + 2] = pixel.getRed();
				}
			}
			BITMAPINFO info;
			info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			info.bmiHeader.biWidth = m_sBuffer.getWidth();
			info.bmiHeader.biHeight = m_sBuffer.getHeight();
			info.bmiHeader.biPlanes = 1;
			info.bmiHeader.biBitCount = 24;
			info.bmiHeader.biCompression = BI_RGB;
			info.bmiHeader.biSizeImage = 0;
			info.bmiHeader.biXPelsPerMeter = 0;
			info.bmiHeader.biYPelsPerMeter = 0;
			info.bmiHeader.biClrImportant = 0;
			info.bmiHeader.biClrUsed = 0;
			SetDIBits(m_hDC, m_hBitmap, m_sBuffer.getHeight() - clip->Bottom, clip->Height(), m_aBuffer, &info, DIB_RGB_COLORS);
			// Draw on window
			HBITMAP old_bmp = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
			BitBlt(dc, 0, clip->Top, m_sBuffer.getWidth(), clip->Height(), m_hDC, 0, clip->Top, SRCCOPY);
			// Finish
			SelectObject(m_hDC, old_bmp);
			ReleaseDC((HWND)m_pWindow->getHandle(), dc);
		}

#pragma region Text
		void CPresenterGDI::RenderString(
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
			const bool blend)
		{
			m_sBuffer.RenderString(str, font, x, y, angle, sx, sy, clip, antialiazing, block_rect, border_width, border_radius, border_antialiazing, location, draw_text, draw_shadow, text_color, shadow_color, fclip, frender, blend);
		}
#pragma endregion

#pragma region Image
		void CPresenterGDI::RenderImage(
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
			const bool blend)
		{
			m_sBuffer.RenderImage(image, image_part, x, y, angle, sx, sy, repeat_x, repeat_y, interpolate, clip, block_rect, border_width, border_radius, border_antialiazing, location, fclip, frender, blend);
		}
#pragma endregion

#pragma region Fill rectangle
		void CPresenterGDI::FillRect(
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
			const bool blend)
		{
			m_sBuffer.FillRect(color, clip, rect, block_rect, border_width, border_radius, border_antialiazing, location, fclip, frender, blend);
		}

		void CPresenterGDI::MultiFillRect(
			const APP_COLOR colors[graphics::bplBottom + 1],
			const APP_RECT &clip,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_width,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			IImage::ICustomClip *fclip,
			IImage::ICustomRender *frender,
			const bool blend)
		{
			m_sBuffer.MultiFillRect(colors, clip, block_rect, border_width, border_radius, border_antialiazing, fclip, frender, blend);
		}

		void CPresenterGDI::RenderBorder(
			const graphics::BLOCK_POINT_LOCATION location,
			const APP_COLOR &color,
			const APP_RECT &clip,
			const APP_RECT &block_rect,
			const math::RECTANGLE<size_t> &border_width,
			const math::RECTANGLE<size_t> &border_radius,
			const size_t border_antialiazing,
			IImage::ICustomClip *fclip,
			IImage::ICustomRender *frender,
			const bool blend)
		{
			m_sBuffer.RenderBorder(location, color, clip, block_rect, border_width, border_radius, border_antialiazing, fclip, frender, blend);
		}
#pragma endregion

#pragma region Free drawing
		void CPresenterGDI::Draw(
			const APP_RECT &clip,
			IImage::ICustomDraw *fdraw)
		{
			m_sBuffer.Draw(clip, fdraw);
		}
#pragma endregion

#pragma region Blur
		void CPresenterGDI::BoxBlur(
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
			const bool blend)
		{
			m_sBuffer.BoxBlur(color, dx, dy, radius, clip, block_rect, border_radius, border_antialiazing, fclip, frender, blend);
		}
#pragma endregion

	#pragma region Gradient
		void CPresenterGDI::RenderGradient(
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
			const bool blend)
		{
			m_sBuffer.RenderGradient(type, point_count, points, location, clip, rect, block_rect, border_width, border_radius, border_antialiazing, fclip, frender, blend);
		}
	#pragma endregion
	}
}