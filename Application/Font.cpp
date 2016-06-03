// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "Font.h"

namespace licui
{
	namespace application
	{
#pragma region CFontData
		CFontData::CFontData() :
			m_sName{ L"Tahoma" },
			m_iHeight{ -11 },
			m_iWeight{ 400 },
			m_bItalic{ false },
			m_bUnderline{ false },
			m_bStrikeOut{ false },
			m_iWidth{ 0 },
			m_iCharSet{ 0 },
			m_iQuality{ 0 },
			m_iPitchAndFamily{ 0 },
			m_iOrientation{ 0 },
			m_iDistance{ 0 },
			m_bShadow{ false },
			m_sShadowShift{ 0, 0 },
			m_iShadowBlur{ 0 },
			m_sShadowColor{ 0, 0, 0, 255 },
			m_sColor{ 0, 0, 0, 255 },
			m_bInterpolate{ false }
		{

		}

		String CFontData::getName() const
		{
			return m_sName;
		}

		int CFontData::getHeight() const
		{
			return m_iHeight;
		}

		int CFontData::getWeight() const
		{
			return m_iWeight;
		}

		bool CFontData::getItalic() const
		{
			return m_bItalic;
		}

		bool CFontData::getUnderline() const
		{
			return m_bUnderline;
		}

		bool CFontData::getStrikeOut() const
		{
			return m_bStrikeOut;
		}

		int CFontData::getWidth() const
		{
			return m_iWidth;
		}

		unsigned int CFontData::getCharSet() const
		{
			return m_iCharSet;
		}

		unsigned int CFontData::getQuality() const
		{
			return m_iQuality;
		}

		unsigned int CFontData::getPitchAndFamily() const
		{
			return m_iPitchAndFamily;
		}

		int CFontData::getOrientation() const
		{
			return m_iOrientation;
		}

		int CFontData::getDistance() const
		{
			return m_iDistance;
		}

		bool CFontData::getShadow() const
		{
			return m_bShadow;
		}

		APP_POINT CFontData::getShadowShift() const
		{
			return m_sShadowShift;
		}

		int CFontData::getShadowShiftX() const
		{
			return m_sShadowShift.X;
		}

		int CFontData::getShadowShiftY() const
		{
			return m_sShadowShift.Y;
		}

		size_t CFontData::getShadowBlur() const
		{
			return m_iShadowBlur;
		}

		APP_COLOR CFontData::getShadowColor() const
		{
			return m_sShadowColor;
		}

		APP_COLOR CFontData::getColor() const
		{
			return m_sColor;
		}

		bool CFontData::getInterpolate() const
		{
			return m_bInterpolate;
		}

		void CFontData::setName(const String &value)
		{
			m_sName = value;
		}

		void CFontData::setHeight(const int value)
		{
			m_iHeight = value;
		}

		void CFontData::setWeight(const int value)
		{
			m_iWeight = value;
		}

		void CFontData::setItalic(const bool value)
		{
			m_bItalic = value;
		}

		void CFontData::setUnderline(const bool value)
		{
			m_bUnderline = value;
		}

		void CFontData::setStrikeOut(const bool value)
		{
			m_bStrikeOut = value;
		}

		void CFontData::setWidth(const int value)
		{
			m_iWidth = value;
		}

		void CFontData::setCharSet(const unsigned int value)
		{
			m_iCharSet = value;
		}

		void CFontData::setQuality(const unsigned int value)
		{
			m_iQuality = value;
		}

		void CFontData::setPitchAndFamily(const unsigned int value)
		{
			m_iPitchAndFamily = value;
		}

		void CFontData::setOrientation(const int value)
		{
			m_iOrientation = value;
		}

		void CFontData::setDistance(const int value)
		{
			m_iDistance = value;
		}

		void CFontData::setShadow(const bool value)
		{
			m_bShadow = value;
		}

		void CFontData::setShadowShift(const APP_POINT &value)
		{
			m_sShadowShift = value;
		}

		void CFontData::setShadowShift(const int x, const int y)
		{
			m_sShadowShift = { x, y };
		}

		void CFontData::setShadowShiftX(const int value)
		{
			m_sShadowShift.X = value;
		}

		void CFontData::setShadowShiftY(const int value)
		{
			m_sShadowShift.Y = value;
		}

		void CFontData::setShadowBlur(const size_t value)
		{
			m_iShadowBlur = value;
		}

		void CFontData::setShadowColor(const APP_COLOR &value)
		{
			m_sShadowColor = value;
		}

		void CFontData::setShadowColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
		{
			m_sShadowColor = { r, g, b, a };
		}

		void CFontData::setColor(const APP_COLOR &value)
		{
			m_sColor = value;
		}

		void CFontData::setColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
		{
			m_sColor = { r, g, b, a };
		}

		void CFontData::setInterpolate(const bool value)
		{
			m_bInterpolate = value;
		}
#pragma endregion

#pragma region IFont
		IFont::IFont() : CFontData(),
			m_pCallbackParam{ nullptr },
			m_fOnChangeName{ nullptr },
			m_fOnChangeHeight{ nullptr },
			m_fOnChangeWeight{ nullptr },
			m_fOnChangeItalic{ nullptr },
			m_fOnChangeUnderline{ nullptr },
			m_fOnChangeStrikeOut{ nullptr },
			m_fOnChangeWidth{ nullptr },
			m_fOnChangeCharSet{ nullptr },
			m_fOnChangeQuality{ nullptr },
			m_fOnChangePitchAndFamily{ nullptr },
			m_fOnChangeOrientation{ nullptr },
			m_fOnChangeDistance{ nullptr },
			m_fOnChangeShadow{ nullptr },
			m_fOnChangeShadowShift{ nullptr },
			m_fOnChangeShadowBlur{ nullptr },
			m_fOnChangeShadowColor{ nullptr },
			m_fOnChangeColor{ nullptr },
			m_fOnChangeInterpolate{ nullptr },
			m_fOnBeginChange{ nullptr },
			m_fOnEndChange{ nullptr }
		{

		}

		IFont::~IFont()
		{

		}

		void *IFont::getCallbackParam() const
		{
			return m_pCallbackParam;
		}

		IFont::FOnChangeName IFont::getOnChangeName() const
		{
			return m_fOnChangeName;
		}

		IFont::FOnChangeHeight IFont::getfOnChangeHeight() const
		{
			return m_fOnChangeHeight;
		}

		IFont::FOnChangeWeight IFont::getOnChangeWeight() const
		{
			return m_fOnChangeWeight;
		}

		IFont::FOnChangeItalic IFont::getOnChangeItalic() const
		{
			return m_fOnChangeItalic;
		}

		IFont::FOnChangeUnderline IFont::getOnChangeUnderline() const
		{
			return m_fOnChangeUnderline;
		}

		IFont::FOnChangeStrikeOut IFont::getOnChangeStrikeOut() const
		{
			return m_fOnChangeStrikeOut;
		}

		IFont::FOnChangeWidth IFont::getOnChangeWidth() const
		{
			return m_fOnChangeWidth;
		}

		IFont::FOnChangeCharSet IFont::getOnChangeCharSet() const
		{
			return m_fOnChangeCharSet;
		}

		IFont::FOnChangeQuality IFont::getOnChangeQuality() const
		{
			return m_fOnChangeQuality;
		}

		IFont::FOnChangePitchAndFamily IFont::getOnChangePitchAndFamily() const
		{
			return m_fOnChangePitchAndFamily;
		}

		IFont::FOnChangeOrientation IFont::getOnChangeOrientation() const
		{
			return m_fOnChangeOrientation;
		}

		IFont::FOnChangeDistance IFont::getOnChangeDistance() const
		{
			return m_fOnChangeDistance;
		}

		IFont::FOnChangeShadow IFont::getOnChangeShadow() const
		{
			return m_fOnChangeShadow;
		}

		IFont::FOnChangeShadowShift IFont::getOnChangeShadowShift() const
		{
			return m_fOnChangeShadowShift;
		}

		IFont::FOnChangeShadowBlur IFont::getOnChangeShadowBlur() const
		{
			return m_fOnChangeShadowBlur;
		}

		IFont::FOnChangeShadowColor IFont::getOnChangeShadowColor() const
		{
			return m_fOnChangeShadowColor;
		}
		
		IFont::FOnChangeColor IFont::getOnChangeColor() const
		{
			return m_fOnChangeColor;
		}

		IFont::FOnChangeInterpolate IFont::getOnChangeInterpolate() const
		{
			return m_fOnChangeInterpolate;
		}

		IFont::FOnBeginChange IFont::getOnBeginChange() const
		{
			return m_fOnBeginChange;
		}

		IFont::FOnEndChange IFont::getOnEndChange() const
		{
			return m_fOnEndChange;
		}

		IFont *IFont::setCallbackParam(void *value)
		{
			m_pCallbackParam = value;
			return this;
		}

		IFont *IFont::setOnChangeName(FOnChangeName value)
		{
			m_fOnChangeName = value;
			return this;
		}

		IFont *IFont::setOnChangeHeight(FOnChangeHeight value)
		{
			m_fOnChangeHeight = value;
			return this;
		}

		IFont *IFont::setOnChangeWeight(FOnChangeWeight value)
		{
			m_fOnChangeWeight = value;
			return this;
		}

		IFont *IFont::setOnChangeItalic(FOnChangeItalic value)
		{
			m_fOnChangeItalic = value;
			return this;
		}

		IFont *IFont::setOnChangeUnderline(FOnChangeUnderline value)
		{
			m_fOnChangeUnderline = value;
			return this;
		}

		IFont *IFont::setOnChangeStrikeOut(FOnChangeStrikeOut value)
		{
			m_fOnChangeStrikeOut = value;
			return this;
		}

		IFont *IFont::setOnChangeWidth(FOnChangeWidth value)
		{
			m_fOnChangeWidth = value;
			return this;
		}

		IFont *IFont::setOnChangeCharSet(FOnChangeCharSet value)
		{
			m_fOnChangeCharSet = value;
			return this;
		}

		IFont *IFont::setOnChangeQuality(FOnChangeQuality value)
		{
			m_fOnChangeQuality = value;
			return this;
		}

		IFont *IFont::setOnChangePitchAndFamily(FOnChangePitchAndFamily value)
		{
			m_fOnChangePitchAndFamily = value;
			return this;
		}

		IFont *IFont::setOnChangeOrientation(FOnChangeOrientation value)
		{
			m_fOnChangeOrientation = value;
			return this;
		}

		IFont *IFont::setOnChangeDistance(FOnChangeDistance value)
		{
			m_fOnChangeDistance = value;
			return this;
		}

		IFont *IFont::setOnChangeShadow(FOnChangeShadow value)
		{
			m_fOnChangeShadow = value;
			return this;
		}

		IFont *IFont::setOnChangeShadowShift(FOnChangeShadowShift value)
		{
			m_fOnChangeShadowShift = value;
			return this;
		}

		IFont *IFont::setOnChangeShadowBlur(FOnChangeShadowBlur value)
		{
			m_fOnChangeShadowBlur = value;
			return this;
		}

		IFont *IFont::setOnChangeShadowColor(FOnChangeShadowColor value)
		{
			m_fOnChangeShadowColor = value;
			return this;
		}

		IFont *IFont::setOnChangeColor(FOnChangeColor value)
		{
			m_fOnChangeColor = value;
			return this;
		}

		IFont *IFont::setOnChangeInterpolate(FOnChangeInterpolate value)
		{
			m_fOnChangeInterpolate = value;
			return this;
		}

		IFont *IFont::setOnBeginChange(FOnBeginChange value)
		{
			m_fOnBeginChange = value;
			return this;
		}

		IFont *IFont::setOnEndChange(FOnEndChange value)
		{
			m_fOnEndChange = value;
			return this;
		}

		IFont *IFont::BeginChange()
		{
			if (m_fOnBeginChange)
				m_fOnBeginChange(m_pCallbackParam);
			return this;
		}

		IFont *IFont::EndChange()
		{
			if (m_fOnEndChange)
				m_fOnEndChange(m_pCallbackParam);
			return this;
		}
#pragma endregion
	}
}