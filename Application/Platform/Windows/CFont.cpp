// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "CPresenterGDI.h"

namespace licui
{
	namespace application
	{
#pragma region Construction/Destruction
		CFont::CFont(CPresenterGDI *presenter, CFontData *data) :
			IFont(),
			m_hFont{ 0 },
			m_bIsCharsSorted{ false },
			m_pPresenter{ presenter }
		{
			m_sName = data->getName();
			m_iHeight = data->getHeight();
			m_iWeight = data->getWeight();
			m_bItalic = data->getItalic();
			m_bUnderline = data->getUnderline();
			m_bStrikeOut = data->getStrikeOut();
			m_iWidth = data->getWidth();
			m_iCharSet = data->getCharSet();
			m_iQuality = data->getQuality();
			m_iPitchAndFamily = data->getPitchAndFamily();
			m_iOrientation = data->getOrientation();
			m_iDistance = data->getDistance();
			m_bShadow = data->getShadow();
			m_sShadowShift = data->getShadowShift();
			m_iShadowBlur = data->getShadowBlur();
			m_sShadowColor = data->getShadowColor();
			m_sColor = data->getColor();
			m_bInterpolate = data->getInterpolate();
			Recreate();
		}

		CFont::~CFont()
		{
			ClearChars();
			if (m_hFont)
				DeleteObject(m_hFont);
		}

		void CFont::Recreate()
		{
			if (m_hFont)
				DeleteObject(m_hFont);
			ClearChars();
			m_hFont = CreateFontW(m_iHeight, m_iWidth, 0, 0, m_iWeight, m_bItalic, m_bUnderline, m_bStrikeOut, m_iCharSet, OUT_DEFAULT_PRECIS,
				CLIP_DEFAULT_PRECIS, m_iQuality, m_iPitchAndFamily, m_sName.c_str());
		}
#pragma endregion

#pragma region Getters
		bool CFont::getIsValid() const
		{
			return m_hFont != 0;
		}

		APP_POINT CFont::getStringSize(const String &str)
		{
			APP_POINT result{ 0, 0 };
			GLYPH *img{ nullptr };
			if (str.length() == 1 && std::isspace(str[0], std::locale()) && (img = getChar(str[0])))
				return{ (int)img->Width, (int)img->Height };
			bool first{ true };
			for (const wchar_t c : str)
			{
				img = getChar(c);
				if (!img)
					continue;
				if (first)
				{
					result.X += img->Image.getWidth();
					first = false;
				}
				else
					result.X += img->Width;
				result.Y = (std::max)(result.Y, (int)img->Image.getHeight());
			}
			if (m_bShadow)
				result.X += std::abs(m_sShadowShift.X) + m_iShadowBlur;
			result.X += m_iDistance * (str.length() - 1);
			return result;
		}
#pragma endregion

#pragma region Setters
		IFont *CFont::setHeight(const int value)
		{
			if (value != m_iHeight)
			{
				m_iHeight = value;
				Recreate();
				if (m_fOnChangeHeight)
					m_fOnChangeHeight(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setWidth(const int value)
		{
			if (value != m_iWidth)
			{
				m_iWidth = value;
				Recreate();
				if (m_fOnChangeWidth)
					m_fOnChangeWidth(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setWeight(const int value)
		{
			if (value != m_iWeight)
			{
				m_iWeight = value;
				Recreate();
				if (m_fOnChangeWeight)
					m_fOnChangeWeight(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setItalic(const bool value)
		{
			if (value != m_bItalic)
			{
				m_bItalic = value;
				Recreate();
				if (m_fOnChangeItalic)
					m_fOnChangeItalic(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setUnderline(const bool value)
		{
			if (value != m_bUnderline)
			{
				m_bUnderline = value;
				Recreate();
				if (m_fOnChangeUnderline)
					m_fOnChangeUnderline(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setStrikeOut(const bool value)
		{
			if (value != m_bStrikeOut)
			{
				m_bStrikeOut = value;
				Recreate();
				if (m_fOnChangeStrikeOut)
					m_fOnChangeStrikeOut(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setCharSet(const unsigned int value)
		{
			if (value != m_iCharSet)
			{
				m_iCharSet = value;
				Recreate();
				if (m_fOnChangeCharSet)
					m_fOnChangeCharSet(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setQuality(const unsigned int value)
		{
			if (value != m_iQuality)
			{
				m_iQuality = value;
				Recreate();
				if (m_fOnChangeQuality)
					m_fOnChangeQuality(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setPitchAndFamily(const unsigned int value)
		{
			if (value != m_iPitchAndFamily)
			{
				m_iPitchAndFamily = value;
				Recreate();
				if (m_fOnChangePitchAndFamily)
					m_fOnChangePitchAndFamily(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setOrientation(const int value)
		{
			if (value != m_iOrientation)
			{
				m_iOrientation = value;
				if (m_fOnChangeOrientation)
					m_fOnChangeOrientation(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setName(const String &value)
		{
			if (value != m_sName)
			{
				m_sName = value;
				Recreate();
				if (m_fOnChangeName)
					m_fOnChangeName(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setShadow(const bool value)
		{
			if (value != m_bShadow)
			{
				m_bShadow = value;
				Recreate();
				if (m_fOnChangeShadow)
					m_fOnChangeShadow(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setShadowShift(const APP_POINT &value)
		{
			if (value != m_sShadowShift)
			{
				m_sShadowShift = value;
				if (m_bShadow)
					Recreate();
				if (m_fOnChangeShadowShift)
					m_fOnChangeShadowShift(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setShadowShift(const int x, const int y)
		{
			if (x != m_sShadowShift.X || y != m_sShadowShift.Y)
			{
				m_sShadowShift.X = x;
				m_sShadowShift.Y = y;
				if (m_bShadow)
					Recreate();
				if (m_fOnChangeShadowShift)
					m_fOnChangeShadowShift(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setShadowShiftX(const int value)
		{
			if (value != m_sShadowShift.X)
			{
				m_sShadowShift.X = value;
				if (m_bShadow)
					Recreate();
				if (m_fOnChangeShadowShift)
					m_fOnChangeShadowShift(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setShadowShiftY(const int value)
		{
			if (value != m_sShadowShift.Y)
			{
				m_sShadowShift.Y = value;
				if (m_bShadow)
					Recreate();
				if (m_fOnChangeShadowShift)
					m_fOnChangeShadowShift(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setShadowBlur(const size_t value)
		{
			if (value != m_iShadowBlur)
			{
				m_iShadowBlur = value;
				if (m_bShadow)
					Recreate();
				if (m_fOnChangeShadowBlur)
					m_fOnChangeShadowBlur(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setDistance(const int value)
		{
			if (value != m_iDistance)
			{
				m_iDistance = value;
				if (m_fOnChangeDistance)
					m_fOnChangeDistance(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setColor(const APP_COLOR &value)
		{
			if ((graphics::PIXEL<unsigned char, 4>)value != m_sColor)
			{
				m_sColor = value;
				if (m_fOnChangeColor)
					m_fOnChangeColor(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
		{
			if (r != m_sColor.getRed() || g != m_sColor.getGreen() || b != m_sColor.getBlue() || a != m_sColor.getAlpha())
			{
				m_sColor.setRed(r);
				m_sColor.setGreen(g);
				m_sColor.setBlue(b);
				m_sColor.setAlpha(a);
				if (m_fOnChangeColor)
					m_fOnChangeColor(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setShadowColor(const APP_COLOR &value)
		{
			if ((graphics::PIXEL<unsigned char, 4>)value != m_sShadowColor)
			{
				m_sShadowColor = value;
				if (m_fOnChangeShadowColor)
					m_fOnChangeShadowColor(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setShadowColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
		{
			if (r != m_sShadowColor.getRed() || g != m_sShadowColor.getGreen() || b != m_sShadowColor.getBlue() || a != m_sShadowColor.getAlpha())
			{
				m_sShadowColor.setRed(r);
				m_sShadowColor.setGreen(g);
				m_sShadowColor.setBlue(b);
				m_sShadowColor.setAlpha(a);
				if (m_fOnChangeShadowColor)
					m_fOnChangeShadowColor(m_pCallbackParam);
			}
			return this;
		}

		IFont *CFont::setInterpolate(const bool value)
		{
			if (value != m_bInterpolate)
			{
				m_bInterpolate = value;
				if (m_fOnChangeInterpolate)
					m_fOnChangeInterpolate(m_pCallbackParam);
			}
			return this;
		}
#pragma endregion

#pragma region Chars management
		void CFont::ClearChars()
		{
			for (auto pos = m_aChars.begin(); pos != m_aChars.end(); pos++)
			{
				(*pos)->Data.Image.Free();
				delete (*pos);
			}
			m_aChars.clear();
			m_bIsCharsSorted = true;
		}

		void CFont::SortChars()
		{
			if (!m_bIsCharsSorted)
			{
				std::sort(m_aChars.begin(), m_aChars.end(), [](const CHAR_IMAGE *a, const CHAR_IMAGE *b) { return a->Char < b->Char; });
				m_bIsCharsSorted = true;
			}
		}

		int CFont::FindCharIndex(const wchar_t chr)
		{
			SortChars();
			m_sSearchChar.Char = chr;
			auto pos = std::lower_bound(m_aChars.begin(), m_aChars.end(), &m_sSearchChar, [](const CHAR_IMAGE *a, const CHAR_IMAGE *b) {return a->Char < b->Char; });
			if (pos == m_aChars.end())
				return -1;
			if ((*pos)->Char != chr)
				return -1;
			return pos - m_aChars.begin();
		}

		IFont::GLYPH *CFont::getChar(const wchar_t chr)
		{
			if (!m_hFont)
				return nullptr;
			if (!std::isgraph(chr, std::locale()) && !std::isspace(chr, std::locale()))
				return nullptr;
			int index = FindCharIndex(chr);
			if (index >= 0)
				return &(m_aChars[index]->Data);
			CHAR_IMAGE *img = CreateChar(chr);
			if (!img)
				return nullptr;
			m_aChars.push_back(img);
			m_bIsCharsSorted = false;
			return &img->Data;
		}

		CFont::CHAR_IMAGE *CFont::CreateChar(const wchar_t chr)
		{
			HDC dc = m_pPresenter->getDC();
			if (!dc)
				return nullptr;
			// Set font
			HFONT old_font = (HFONT)SelectObject(dc, m_hFont);
			// Try get char sizes
			SIZE size;
			if (!GetTextExtentPoint32W(dc, &chr, 1, &size))
			{
				SelectObject(dc, old_font);
				return nullptr;
			}
			// Create bitmap where to paint
			HBITMAP bmp = CreateCompatibleBitmap(dc, size.cx * 2, size.cy);
			if (!bmp)
			{
				SelectObject(dc, old_font);
				return nullptr;
			}
			HBITMAP old_bmp = (HBITMAP)SelectObject(dc, bmp);
			// Prepare painting
			SetTextColor(dc, 0x00FFFFFF);
			SetBkColor(dc, 0x00000000);
			HBRUSH brush = CreateSolidBrush(0x00000000);
			RECT rect = { 0, 0, size.cx * 2, size.cy };
			FillRect(dc, &rect, brush);
			DeleteObject(brush);
			// Draw text & select old font and bmp
			TextOutW(dc, 0, 0, &chr, 1);
			SelectObject(dc, old_bmp);
			SelectObject(dc, old_font);
			// Try get bitmap data
			BITMAPINFO info;
			info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			info.bmiHeader.biWidth = size.cx * 2;
			info.bmiHeader.biHeight = size.cy;
			info.bmiHeader.biPlanes = 1;
			info.bmiHeader.biBitCount = 24;
			info.bmiHeader.biCompression = BI_RGB;
			info.bmiHeader.biSizeImage = 0;
			info.bmiHeader.biXPelsPerMeter = 0;
			info.bmiHeader.biYPelsPerMeter = 0;
			info.bmiHeader.biClrImportant = 0;
			info.bmiHeader.biClrUsed = 0;
			int pitch = ((size.cx * 2 * 3 + 3) / sizeof(DWORD)) * sizeof(DWORD);
			unsigned char *bits = new unsigned char[pitch * size.cy];
			int lines = GetDIBits(dc, bmp, 0, size.cy, bits, &info, DIB_RGB_COLORS);
			DeleteObject(bmp);
			// Check data was received
			if (!lines)
			{
				delete[] bits;
				return nullptr;
			}
			// Convert data to image
			int disp_x{ 0 }, disp_y{ 0 }, dw{ 0 }, dh{ 0 };
			if (m_bShadow)
			{
				dw = abs(m_sShadowShift.X) + m_iShadowBlur;
				dh = abs(m_sShadowShift.Y) + m_iShadowBlur;
				if (m_sShadowShift.X < 0)
					disp_x = dw;
				if (m_sShadowShift.Y < 0)
					disp_y = dh;
			}
			// Calc real width;
			int x1{ size.cx * 2 - 1 }, x2{ 0 }, x, y, w;
			unsigned char *scanline;
			for (y = 0; y < lines; y++)
			{
				scanline = &bits[pitch * (lines - y - 1)];
				for (x = 0; x < size.cx * 2; x++)
					if (scanline[x * 3] > 0)
					{
						x1 = (std::min)(x1, x);
						x2 = (std::max)(x2, x);
					}
			}
			w = x2 + 1 + x1;
			CHAR_IMAGE *image = new CHAR_IMAGE{ chr,{ (size_t)size.cx, (size_t)lines, (size_t)disp_x, (size_t)disp_y } };
			image->Data.Image.Alloc(w + dw, lines + dh);
			image->Data.Image.FillChannel(0, 0);
			for (y = 0; y < lines; y++)
			{
				scanline = &bits[pitch * (lines - y - 1)];
				for (x = 0; x < w; x++)
					image->Data.Image[x + disp_x][y + disp_y][0] = scanline[x * 3];
			}
			delete[] bits;
			if (m_bShadow)
			{
				int y1;
				for (y = 0; y < (int)image->Data.Image.getHeight(); y++)
				{
					y1 = y - m_sShadowShift.Y;
					for (x = 0; x < (int)image->Data.Image.getWidth(); x++)
					{
						x1 = x - m_sShadowShift.X;
						if (x1 >= 0 && x1 < (int)image->Data.Image.getWidth() && y1 >= 0 && y1 < (int)image->Data.Image.getHeight())
							image->Data.Image[x][y][1] = image->Data.Image[x1][y1][0];
						else
							image->Data.Image[x][y][1] = 0;
					}
				}
				image->Data.Image.Blur(1, 2, m_iShadowBlur, { 0, 0, image->Data.Image.getWidth(), image->Data.Image.getHeight() });
			}
			return image;
		}

		void CFont::AddCharacters(const String &str)
		{
			if (!m_hFont)
				return;
			if (str.empty())
				return;
			// Build list of chars to be added
			String sorted{ str };
			std::sort(sorted.begin(), sorted.end());
			wchar_t last = sorted[0] - 1;
			std::vector<wchar_t> to_add;
			for (const wchar_t &c : sorted)
				if (c != last && (std::isgraph(c, std::locale()) || std::isspace(c, std::locale())))
				{
					if (FindCharIndex(c) < 0)
						to_add.push_back(c);
					last = c;
				}
			// Create chars
			if (to_add.empty())
				return;
			CHAR_IMAGE *img;
			for (wchar_t &c : to_add)
			{
				img = CreateChar(c);
				if (!img)
					return;
				m_aChars.push_back(img);
				m_bIsCharsSorted = false;
			}
		}
#pragma endregion
	}
}