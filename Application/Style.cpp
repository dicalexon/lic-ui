// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include <algorithm>
#include "StyleImage.h"
#include "StyleSkin.h"
#include "StyleFont.h"
#include "Style.h"

namespace licui
{
	namespace application
	{
		CStyle::PARAMETER::PARAMETER() :
			Name{ L"" },
			Type{ sptInteger },
			ValueS{ L"" },
			RectUnsigned{ 0, 0, 0, 0 }
		{

		}

		CStyle::CStyle() :
			m_bImagesSorted{ true },
			m_bSkinsSorted{ true },
			m_bFontsSorted{ true },
			m_bParametersSorted{ true }
		{

		}

		CStyle::~CStyle()
		{
			for (auto pos = m_aImages.begin(); pos != m_aImages.end(); pos++)
				delete (*pos);
			for (auto pos = m_aSkins.begin(); pos != m_aSkins.end(); pos++)
				delete (*pos);
			for (auto pos = m_aFonts.begin(); pos != m_aFonts.end(); pos++)
				delete (*pos);
			for (auto pos = m_aParameters.begin(); pos != m_aParameters.end(); pos++)
				delete (*pos);
		}

		void CStyle::SortImages()
		{
			if (!m_bImagesSorted)
			{
				std::sort(m_aImages.begin(), m_aImages.end(), [](const CStyleImage *a, const CStyleImage *b) { return a->getClassName() < b->getClassName(); });
				m_bImagesSorted = true;
			}
		}

		void CStyle::SortSkins()
		{
			if (!m_bSkinsSorted)
			{
				std::sort(m_aSkins.begin(), m_aSkins.end(), [](const CStyleSkin *a, const CStyleSkin *b) { return a->getClassName() < b->getClassName(); });
				m_bSkinsSorted = true;
			}
		}

		void CStyle::SortFonts()
		{
			if (!m_bFontsSorted)
			{
				std::sort(m_aFonts.begin(), m_aFonts.end(), [](const CStyleFont *a, const CStyleFont *b) { return a->getClassName() < b->getClassName(); });
				m_bFontsSorted = true;
			}
		}

		void CStyle::SortParameters()
		{
			if (!m_bParametersSorted)
			{
				std::sort(m_aParameters.begin(), m_aParameters.end(), [](const PARAMETER *a, const PARAMETER *b) { return a->Name < b->Name; });
				m_bParametersSorted = true;
			}
		}

		int CStyle::FindImageIndex(const String &name)
		{
			SortImages();
			CStyleSkin search{ ToLower(name), nullptr };
			auto pos = std::lower_bound(m_aSkins.begin(), m_aSkins.end(), &search, [](const CStyleSkin *a, const CStyleSkin *b) { return a->getClassName() < b->getClassName(); });
			if (pos == m_aSkins.end())
				return -1;
			if ((*pos)->getClassName() != search.getClassName())
				return -1;
			return pos - m_aSkins.begin();
		}

		int CStyle::FindSkinIndex(const String &name)
		{
			SortSkins();
			CStyleSkin search{ ToLower(name), nullptr };
			auto pos = std::lower_bound(m_aSkins.begin(), m_aSkins.end(), &search, [](const CStyleSkin *a, const CStyleSkin *b) { return a->getClassName() < b->getClassName(); });
			if (pos == m_aSkins.end())
				return -1;
			if ((*pos)->getClassName() != search.getClassName())
				return -1;
			return pos - m_aSkins.begin();
		}

		int CStyle::FindFontIndex(const String &name)
		{
			SortFonts();
			CStyleFont search{ ToLower(name) };
			auto pos = std::lower_bound(m_aFonts.begin(), m_aFonts.end(), &search, [](const CStyleFont *a, const CStyleFont *b) { return a->getClassName() < b->getClassName(); });
			if (pos == m_aFonts.end())
				return -1;
			if ((*pos)->getClassName() != search.getClassName())
				return -1;
			return pos - m_aFonts.begin();
		}

		int CStyle::FindParameterIndex(const String &name)
		{
			SortParameters();
			PARAMETER search;
			search.Name = ToLower(name);
			auto pos = std::lower_bound(m_aParameters.begin(), m_aParameters.end(), &search, [](const PARAMETER *a, const PARAMETER *b) { return a->Name < b->Name; });
			if (pos == m_aParameters.end())
				return -1;
			if ((*pos)->Name != search.Name)
				return -1;
			return pos - m_aParameters.begin();
		}

		CStyleImage *CStyle::ImageAdd(const String &name)
		{
			if (name.empty())
				return nullptr;
			CStyleImage *result = getImageByName(name);
			if (result)
				return result;
			result = new CStyleImage(ToLower(name));
			m_aImages.push_back(result);
			m_bImagesSorted = false;
			return result;
		}

		CStyleSkin *CStyle::SkinAdd(const String &name, CStyleImage *image)
		{
			if (name.empty())
				return nullptr;
			CStyleSkin *result = getSkinByName(name);
			if (result)
				return result;
			result = new CStyleSkin(ToLower(name), image);
			m_aSkins.push_back(result);
			m_bSkinsSorted = false;
			return result;
		}

		CStyleFont *CStyle::FontAdd(const String &name)
		{
			if (name.empty())
				return nullptr;
			CStyleFont *result = getFontByName(name);
			if (result)
				return result;
			result = new CStyleFont(ToLower(name));
			m_aFonts.push_back(result);
			m_bFontsSorted = false;
			return result;
		}

		void CStyle::ParameterAdd(const String &name, const String &value)
		{
			if (name.empty() || value.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->ValueS = value;
			result->Type = sptString;
		}

		void CStyle::ParameterAdd(const String &name, const int value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->Integer = value;
			result->Type = sptInteger;
		}

		void CStyle::ParameterAdd(const String &name, const double value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->Double = value;
			result->Type = sptDouble;
		}

		void CStyle::ParameterAdd(const String &name, const bool value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->Bool = value;
			result->Type = sptBool;
		}

		void CStyle::ParameterAdd(const String &name, const size_t value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->Size = value;
			result->Type = sptSize;
		}

		void CStyle::ParameterAdd(const String &name, const APP_RECT &value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->RectSigned = value;
			result->Type = sptRectSigned;
		}

		void CStyle::ParameterAdd(const String &name, const math::RECTANGLE<size_t> &value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->RectUnsigned = value;
			result->Type = sptRectUnsigned;
		}

		void CStyle::ParameterAdd(const String &name, const math::RECTANGLE<bool> &value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->RectBool = value;
			result->Type = sptRectBool;
		}

		void CStyle::ParameterAdd(const String &name, const APP_COLOR &value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->Color = value;
			result->Type = sptColor;
		}

		void CStyle::ParameterAdd(const String &name, const APP_POINT &value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->PointSigned = value;
			result->Type = sptPointSigned;
		}

		void CStyle::ParameterAdd(const String &name, const math::POINT<size_t> &value)
		{
			if (name.empty())
				return;
			int index{ FindParameterIndex(name) };
			PARAMETER *result;
			if (index < 0)
			{
				result = new PARAMETER;
				result->Name = ToLower(name);
				m_aParameters.push_back(result);
				m_bParametersSorted = false;
			}
			else
				result = m_aParameters[index];
			result->PointUnsigned = value;
			result->Type = sptPointUnsigned;
		}

		String CStyle::getName() const
		{
			return m_sName;
		}

		size_t CStyle::getImageCount() const
		{
			return m_aImages.size();
		}

		CStyleImage *CStyle::getImage(const size_t index)
		{
			if (index < m_aImages.size())
			{
				SortImages();
				return m_aImages[index];
			}
			return nullptr;
		}

		CStyleImage *CStyle::getImageByName(const String &name)
		{
			return getImage(FindImageIndex(name));
		}

		size_t CStyle::getSkinCount() const
		{
			return m_aSkins.size();
		}

		CStyleSkin *CStyle::getSkin(const size_t index)
		{
			if (index < m_aSkins.size())
			{
				SortSkins();
				return m_aSkins[index];
			}
			return nullptr;
		}

		CStyleSkin *CStyle::getSkinByName(const String &name)
		{
			return getSkin(FindSkinIndex(name));
		}

		size_t CStyle::getFontCount() const
		{
			return m_aFonts.size();
		}

		CStyleFont *CStyle::getFont(const size_t index)
		{
			if (index < m_aFonts.size())
			{
				SortFonts();
				return m_aFonts[index];
			}
			return nullptr;
		}

		CStyleFont *CStyle::getFontByName(const String &name)
		{
			return getFont(FindFontIndex(name));
		}

		size_t CStyle::getParameterCount() const
		{
			return m_aParameters.size();
		}

		String CStyle::getParameterByName(const String &name, const String &default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->ValueS;
		}

		int CStyle::getParameterByName(const String &name, const int default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->Integer;
		}

		double CStyle::getParameterByName(const String &name, const double default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->Double;
		}

		bool CStyle::getParameterByName(const String &name, const bool default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->Bool;
		}

		size_t CStyle::getParameterByName(const String &name, const size_t default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->Size;
		}

		APP_RECT CStyle::getParameterByName(const String &name, const APP_RECT &default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->RectSigned;
		}

		math::RECTANGLE<size_t> CStyle::getParameterByName(const String &name, const math::RECTANGLE<size_t> &default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->RectUnsigned;
		}

		math::RECTANGLE<bool> CStyle::getParameterByName(const String &name, const math::RECTANGLE<bool> &default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->RectBool;
		}

		APP_COLOR CStyle::getParameterByName(const String &name, const APP_COLOR &default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->Color;
		}

		APP_POINT CStyle::getParameterByName(const String &name, const APP_POINT &default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->PointSigned;
		}

		math::POINT<size_t> CStyle::getParameterByName(const String &name, const math::POINT<size_t> &default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->PointUnsigned;
		}

		math::POINT<double> CStyle::getParameterByName(const String &name, const math::POINT<double> &default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->PointDouble;
		}

		math::POINT<bool> CStyle::getParameterByName(const String &name, const math::POINT<bool> &default_value)
		{
			int index{ FindParameterIndex(name) };
			if (index <= 0)
				return default_value;
			return m_aParameters[index]->PointBool;
		}
	}
}