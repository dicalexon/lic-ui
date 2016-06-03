// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\Strings\Strings.h"
#include "Types.h"

namespace licui
{
	namespace application
	{
		class CFontData
		{
		protected:
			String m_sName;
			int m_iHeight;
			int m_iWeight;
			bool m_bItalic;
			bool m_bUnderline;
			bool m_bStrikeOut;
			int m_iWidth;
			unsigned int m_iCharSet;
			unsigned int m_iQuality;
			unsigned int m_iPitchAndFamily;
			int m_iOrientation;
			int m_iDistance;
			bool m_bShadow;
			APP_POINT m_sShadowShift;
			size_t m_iShadowBlur;
			APP_COLOR m_sShadowColor;
			APP_COLOR m_sColor;
			bool m_bInterpolate;
		public:
			String getName() const;
			int getHeight() const;
			int getWeight() const;
			bool getItalic() const;
			bool getUnderline() const;
			bool getStrikeOut() const;
			int getWidth() const;
			unsigned int getCharSet() const;
			unsigned int getQuality() const;
			unsigned int getPitchAndFamily() const;
			int getOrientation() const;
			int getDistance() const;
			bool getShadow() const;
			APP_POINT getShadowShift() const;
			int getShadowShiftX() const;
			int getShadowShiftY() const;
			size_t getShadowBlur() const;
			APP_COLOR getShadowColor() const;
			APP_COLOR getColor() const;
			bool getInterpolate() const;

			void setName(const String &value);
			void setHeight(const int value);
			void setWeight(const int value);
			void setItalic(const bool value);
			void setUnderline(const bool value);
			void setStrikeOut(const bool value);
			void setWidth(const int value);
			void setCharSet(const unsigned int value);
			void setQuality(const unsigned int value);
			void setPitchAndFamily(const unsigned int value);
			void setOrientation(const int value);
			void setDistance(const int value);
			void setShadow(const bool value);
			void setShadowShift(const APP_POINT &value);
			void setShadowShift(const int x, const int y);
			void setShadowShiftX(const int value);
			void setShadowShiftY(const int value);
			void setShadowBlur(const size_t value);
			void setShadowColor(const APP_COLOR &value);
			void setShadowColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a);
			void setColor(const APP_COLOR &value);
			void setColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a);
			void setInterpolate(const bool value);

			CFontData();
		};

		class IFont : public CFontData
		{
		public:
			struct GLYPH
			{
				size_t Width;
				size_t Height;
				size_t DispX;
				size_t DispY;
				graphics::IMAGE<unsigned char, 3> Image;
			};

			typedef void(*FOnChangeName)(void *param);
			typedef void(*FOnChangeHeight)(void *param);
			typedef void(*FOnChangeWeight)(void *param);
			typedef void(*FOnChangeItalic)(void *param);
			typedef void(*FOnChangeUnderline)(void *param);
			typedef void(*FOnChangeStrikeOut)(void *param);
			typedef void(*FOnChangeWidth)(void *param);
			typedef void(*FOnChangeCharSet)(void *param);
			typedef void(*FOnChangeQuality)(void *param);
			typedef void(*FOnChangePitchAndFamily)(void *param);
			typedef void(*FOnChangeOrientation)(void *param);
			typedef void(*FOnChangeDistance)(void *param);
			typedef void(*FOnChangeShadow)(void *param);
			typedef void(*FOnChangeShadowShift)(void *param);
			typedef void(*FOnChangeShadowBlur)(void *param);
			typedef void(*FOnChangeShadowColor)(void *param);
			typedef void(*FOnChangeColor)(void *param);
			typedef void(*FOnChangeInterpolate)(void *param);
			typedef void(*FOnBeginChange)(void *param);
			typedef void(*FOnEndChange)(void *param);
		protected:
			void *m_pCallbackParam;
			FOnChangeName m_fOnChangeName;
			FOnChangeHeight m_fOnChangeHeight;
			FOnChangeWeight m_fOnChangeWeight;
			FOnChangeItalic m_fOnChangeItalic;
			FOnChangeUnderline m_fOnChangeUnderline;
			FOnChangeStrikeOut m_fOnChangeStrikeOut;
			FOnChangeWidth m_fOnChangeWidth;
			FOnChangeCharSet m_fOnChangeCharSet;
			FOnChangeQuality m_fOnChangeQuality;
			FOnChangePitchAndFamily m_fOnChangePitchAndFamily;
			FOnChangeOrientation m_fOnChangeOrientation;
			FOnChangeDistance m_fOnChangeDistance;
			FOnChangeShadow m_fOnChangeShadow;
			FOnChangeShadowShift m_fOnChangeShadowShift;
			FOnChangeShadowBlur m_fOnChangeShadowBlur;
			FOnChangeShadowColor m_fOnChangeShadowColor;
			FOnChangeColor m_fOnChangeColor;
			FOnChangeInterpolate m_fOnChangeInterpolate;
			FOnBeginChange m_fOnBeginChange;
			FOnEndChange m_fOnEndChange;
		public:
			IFont();
			virtual ~IFont();

			void *getCallbackParam() const;
			FOnChangeName getOnChangeName() const;
			FOnChangeHeight getfOnChangeHeight() const;
			FOnChangeWeight getOnChangeWeight() const;
			FOnChangeItalic getOnChangeItalic() const;
			FOnChangeUnderline getOnChangeUnderline() const;
			FOnChangeStrikeOut getOnChangeStrikeOut() const;
			FOnChangeWidth getOnChangeWidth() const;
			FOnChangeCharSet getOnChangeCharSet() const;
			FOnChangeQuality getOnChangeQuality() const;
			FOnChangePitchAndFamily getOnChangePitchAndFamily() const;
			FOnChangeOrientation getOnChangeOrientation() const;
			FOnChangeDistance getOnChangeDistance() const;
			FOnChangeShadow getOnChangeShadow() const;
			FOnChangeShadowShift getOnChangeShadowShift() const;
			FOnChangeShadowBlur getOnChangeShadowBlur() const;
			FOnChangeShadowColor getOnChangeShadowColor() const;
			FOnChangeColor getOnChangeColor() const;
			FOnChangeInterpolate getOnChangeInterpolate() const;
			FOnBeginChange getOnBeginChange() const;
			FOnEndChange getOnEndChange() const;

			IFont *setCallbackParam(void *value);
			IFont *setOnChangeName(FOnChangeName value);
			IFont *setOnChangeHeight(FOnChangeHeight value);
			IFont *setOnChangeWeight(FOnChangeWeight value);
			IFont *setOnChangeItalic(FOnChangeItalic value);
			IFont *setOnChangeUnderline(FOnChangeUnderline value);
			IFont *setOnChangeStrikeOut(FOnChangeStrikeOut value);
			IFont *setOnChangeWidth(FOnChangeWidth value);
			IFont *setOnChangeCharSet(FOnChangeCharSet value);
			IFont *setOnChangeQuality(FOnChangeQuality value);
			IFont *setOnChangePitchAndFamily(FOnChangePitchAndFamily value);
			IFont *setOnChangeOrientation(FOnChangeOrientation value);
			IFont *setOnChangeDistance(FOnChangeDistance value);
			IFont *setOnChangeShadow(FOnChangeShadow value);
			IFont *setOnChangeShadowShift(FOnChangeShadowShift value);
			IFont *setOnChangeShadowBlur(FOnChangeShadowBlur value);
			IFont *setOnChangeShadowColor(FOnChangeShadowColor value);
			IFont *setOnChangeColor(FOnChangeColor value);
			IFont *setOnChangeInterpolate(FOnChangeInterpolate value);
			IFont *setOnBeginChange(FOnBeginChange value);
			IFont *setOnEndChange(FOnEndChange value);

			virtual GLYPH *getChar(const wchar_t chr) = 0;
			virtual APP_POINT getStringSize(const String &str) = 0;

			virtual IFont *setName(const String &value) = 0;
			virtual IFont *setHeight(const int value) = 0;
			virtual IFont *setWeight(const int value) = 0;
			virtual IFont *setItalic(const bool value) = 0;
			virtual IFont *setUnderline(const bool value) = 0;
			virtual IFont *setStrikeOut(const bool value) = 0;
			virtual IFont *setWidth(const int value) = 0;
			virtual IFont *setCharSet(const unsigned int value) = 0;
			virtual IFont *setQuality(const unsigned int value) = 0;
			virtual IFont *setPitchAndFamily(const unsigned int value) = 0;
			virtual IFont *setOrientation(const int value) = 0;
			virtual IFont *setDistance(const int value) = 0;
			virtual IFont *setShadow(const bool value) = 0;
			virtual IFont *setShadowShift(const APP_POINT &value) = 0;
			virtual IFont *setShadowShift(const int x, const int y) = 0;
			virtual IFont *setShadowShiftX(const int value) = 0;
			virtual IFont *setShadowShiftY(const int value) = 0;
			virtual IFont *setShadowBlur(const size_t value) = 0;
			virtual IFont *setShadowColor(const APP_COLOR &value) = 0;
			virtual IFont *setShadowColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) = 0;
			virtual IFont *setColor(const APP_COLOR &value) = 0;
			virtual IFont *setColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) = 0;
			virtual IFont *setInterpolate(const bool value) = 0;

			virtual void AddCharacters(const String &str) = 0;
			IFont *BeginChange();
			IFont *EndChange();
		};
	}
}