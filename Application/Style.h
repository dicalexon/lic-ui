// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include <vector>
#include "..\Strings\Strings.h"
#include "Types.h"

namespace licui
{
	namespace application
	{
		class CStyle
		{
		private:
			enum PARAMETER_TYPE
			{
				sptString,
				sptInteger,
				sptDouble,
				sptBool,
				sptSize,
				sptRectSigned,
				sptRectUnsigned,
				sptRectBool,
				sptColor,
				sptPointSigned,
				sptPointUnsigned,
				sptPointDouble,
				sptPointBool
			};

			struct PARAMETER
			{
				String Name;
				PARAMETER_TYPE Type;
				String ValueS;
				union
				{
					int Integer;
					double Double;
					bool Bool;
					size_t Size;
					APP_RECT RectSigned;
					math::RECTANGLE<size_t> RectUnsigned;
					math::RECTANGLE<bool> RectBool;
					APP_COLOR Color;
					APP_POINT PointSigned;
					math::POINT<size_t> PointUnsigned;
					math::POINT<double> PointDouble;
					math::POINT<bool> PointBool;
				};

				PARAMETER();
			};
		private:
			std::vector<CStyleImage*> m_aImages;
			std::vector<CStyleSkin*> m_aSkins;
			std::vector<CStyleFont*> m_aFonts;
			std::vector<PARAMETER*> m_aParameters;
			bool m_bImagesSorted;
			bool m_bSkinsSorted;
			bool m_bFontsSorted;
			bool m_bParametersSorted;

			void SortImages();
			void SortSkins();
			void SortFonts();
			void SortParameters();
			int FindImageIndex(const String &name);
			int FindSkinIndex(const String &name);
			int FindFontIndex(const String &name);
			int FindParameterIndex(const String &name);
		protected:
			String m_sName;

			CStyleImage *ImageAdd(const String &name);
			CStyleSkin *SkinAdd(const String &name, CStyleImage *image);
			CStyleFont *FontAdd(const String &name);
			void ParameterAdd(const String &name, const String &value);
			void ParameterAdd(const String &name, const int value);
			void ParameterAdd(const String &name, const double value);
			void ParameterAdd(const String &name, const bool value);
			void ParameterAdd(const String &name, const size_t value);
			void ParameterAdd(const String &name, const APP_RECT &value);
			void ParameterAdd(const String &name, const math::RECTANGLE<size_t> &value);
			void ParameterAdd(const String &name, const math::RECTANGLE<bool> &value);
			void ParameterAdd(const String &name, const APP_COLOR &value);
			void ParameterAdd(const String &name, const APP_POINT &value);
			void ParameterAdd(const String &name, const math::POINT<size_t> &value);
			void ParameterAdd(const String &name, const math::POINT<double> &value);
			void ParameterAdd(const String &name, const math::POINT<bool> &value);
		public:
			String getName() const;
			size_t getImageCount() const;
			CStyleImage *getImage(const size_t index);
			CStyleImage *getImageByName(const String &name);
			size_t getSkinCount() const;
			CStyleSkin *getSkin(const size_t index);
			CStyleSkin *getSkinByName(const String &name);
			size_t getFontCount() const;
			CStyleFont *getFont(const size_t index);
			CStyleFont *getFontByName(const String &name);
			size_t getParameterCount() const;
			String getParameterByName(const String &name, const String &default_value);
			int getParameterByName(const String &name, const int default_value);
			double getParameterByName(const String &name, const double default_value);
			bool getParameterByName(const String &name, const bool default_value);
			size_t getParameterByName(const String &name, const size_t default_value);
			APP_RECT getParameterByName(const String &name, const APP_RECT &default_value);
			math::RECTANGLE<size_t> getParameterByName(const String &name, const math::RECTANGLE<size_t> &default_value);
			math::RECTANGLE<bool> getParameterByName(const String &name, const math::RECTANGLE<bool> &default_value);
			APP_COLOR getParameterByName(const String &name, const APP_COLOR &default_value);
			APP_POINT getParameterByName(const String &name, const APP_POINT &default_value);
			math::POINT<size_t> getParameterByName(const String &name, const math::POINT<size_t> &default_value);
			math::POINT<double> getParameterByName(const String &name, const math::POINT<double> &default_value);
			math::POINT<bool> getParameterByName(const String &name, const math::POINT<bool> &default_value);

			CStyle();
			virtual ~CStyle();
		};
	}
}