// Copyright � 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Control.h"

namespace licui
{
	namespace application
	{
		class CPanel :public CControl
		{
		public:
			enum BEVEL_TYPE
			{
				btRaised,
				btLowered
			};
		private:
			APP_COLOR m_sBackgroundColor;
			APP_COLOR m_sDisabledTextColor;
			APP_COLOR m_sDisabledShadowColor;
			APP_COLOR m_sBevelRaisedColor;
			APP_COLOR m_sBevelLoweredColor;
			APP_COLOR m_sBorderColor;
			APP_COLOR m_sBoxShadowColor;
			BEVEL_TYPE m_eBevelOuterType;
			BEVEL_TYPE m_eBevelInnerType;
			size_t m_iBevelOuterWidth;
			size_t m_iBevelInnerWidth;
			size_t m_iBorderWidth;
			size_t m_iBorderRadius;
			bool m_bBoxShadow;
			APP_POINT m_sBoxShadowShift;
			size_t m_iBoxShadowRadius;
			TEXT_ALIGN m_eCaptionHorizontalAlign;
			VERTICAL_ALIGN m_eCaptionVerticalAlign;
			math::POINT<double> m_sCaptionScale;
			size_t m_iCaptionAntiAliazing;
			math::RECTANGLE<size_t> m_sPadding;
			String m_sCaption;
			size_t m_iBorderAntiAliazing;

			void PaintBackground(APP_RECT clip, APP_RECT &rect);
			void PaintBevelOuter(APP_RECT clip, APP_RECT &rect);
			void PaintBorder(APP_RECT clip, APP_RECT &rect);
			void PaintBevelInner(APP_RECT clip, APP_RECT &rect);
			void PaintCaption(APP_RECT clip, APP_RECT &rect);
			void PaintBoxShadow(APP_RECT clip);
		protected:
			void NotifyOnPaint(APP_RECT clip) override;

			bool UpdateFromStyle() override;
		public:
			APP_RECT getClientRect() override;
			APP_RECT getRenderRect() override;

			virtual APP_COLOR getBackgroundColor() const;
			virtual APP_COLOR getDisabledTextColor() const;
			virtual APP_COLOR getDisabledShadowColor() const;
			virtual APP_COLOR getBevelRaisedColor() const;
			virtual APP_COLOR getBevelLoweredColor() const;
			virtual APP_COLOR getBorderColor() const;
			virtual APP_COLOR getBoxShadowColor() const;
			virtual BEVEL_TYPE getBevelOuterType() const;
			virtual BEVEL_TYPE getBevelInnerType() const;
			virtual size_t getBevelOuterWidth() const;
			virtual size_t getBevelInnerWidth() const;
			virtual size_t getBorderWidth() const;
			virtual size_t getBorderRadius() const;
			virtual bool getBoxShadow() const;
			virtual APP_POINT getBoxShadowShift() const;
			virtual int getBoxShadowShiftX() const;
			virtual int getBoxShadowShiftY() const;
			virtual size_t getBoxShadowRadius() const;
			virtual TEXT_ALIGN getCaptionHorizontalAlign() const;
			virtual VERTICAL_ALIGN getCaptionVerticalAlign() const;
			virtual math::POINT<double> getCaptionScale() const;
			virtual double getCaptionScaleX() const;
			virtual double getCaptionScaleY() const;
			virtual size_t getCaptionAntiAliazing() const;
			virtual math::RECTANGLE<size_t> getPadding() const;
			virtual size_t getPaddingLeft() const;
			virtual size_t getPaddingTop() const;
			virtual size_t getPaddingRight() const;
			virtual size_t getPaddingBottom() const;
			virtual String getCaption() const;
			virtual size_t getBorderAntiAliazing() const;

			virtual CPanel *setBackgroundColor(const APP_COLOR &value);
			virtual CPanel *setDisabledTextColor(const APP_COLOR &value);
			virtual CPanel *setDisabledShadowColor(const APP_COLOR &value);
			virtual CPanel *setBevelRaisedColor(const APP_COLOR &value);
			virtual CPanel *setBevelLoweredColor(const APP_COLOR &value);
			virtual CPanel *setBorderColor(const APP_COLOR &value);
			virtual CPanel *setBoxShadowColor(const APP_COLOR &value);
			virtual CPanel *setBevelOuterType(const BEVEL_TYPE value);
			virtual CPanel *setBevelInnerType(const BEVEL_TYPE value);
			virtual CPanel *setBevelOuterWidth(const size_t value);
			virtual CPanel *setBevelInnerWidth(const size_t value);
			virtual CPanel *setBorderWidth(const size_t value);
			virtual CPanel *setBorderRadius(const size_t value);
			virtual CPanel *setBoxShadow(const bool value);
			virtual CPanel *setBoxShadowShift(const APP_POINT &value);
			virtual CPanel *setBoxShadowShiftX(const int value);
			virtual CPanel *setBoxShadowShiftY(const int value);
			virtual CPanel *setBoxShadowRadius(const size_t value);
			virtual CPanel *setCaptionHorizontalAlign(const TEXT_ALIGN value);
			virtual CPanel *setCaptionVerticalAlign(const VERTICAL_ALIGN value);
			virtual CPanel *setCaptionScale(const math::POINT<double> &value);
			virtual CPanel *setCaptionScaleX(const double value);
			virtual CPanel *setCaptionScaleY(const double value);
			virtual CPanel *setCaptionAntiAliazing(const size_t value);
			virtual CPanel *setPadding(const math::RECTANGLE<size_t> &value);
			virtual CPanel *setPaddingLeft(const size_t value);
			virtual CPanel *setPaddingTop(const size_t value);
			virtual CPanel *setPaddingRight(const size_t value);
			virtual CPanel *setPaddingBottom(const size_t value);
			virtual CPanel *setCaption(const String &value);
			virtual CPanel *setBorderAntiAliazing(const size_t value);

			CPanel();
			CPanel(CForm *form);
			CPanel(CControl *parent);
		public:
			using CControl::getOnMouseMove;
			using CControl::getOnLeftMouseButtonDown;
			using CControl::getOnLeftMouseButtonUp;
			using CControl::getOnLeftMouseButtonDoubleClick;
			using CControl::getOnRightMouseButtonDown;
			using CControl::getOnRightMouseButtonUp;
			using CControl::getOnRightMouseButtonDoubleClick;
			using CControl::getOnMiddleMouseButtonDown;
			using CControl::getOnMiddleMouseButtonUp;
			using CControl::getOnMiddleMouseButtonDoubleClick;
			using CControl::getOnMouseVerticalWheel;
			using CControl::getOnMouseHorizontalWheel;
			using CControl::getOnChangeUseParentFont;
			using CControl::getOnParentFontChangeName;
			using CControl::getOnParentFontChangeHeight;
			using CControl::getOnParentFontChangeWeight;
			using CControl::getOnParentFontChangeItalic;
			using CControl::getOnParentFontChangeUnderline;
			using CControl::getOnParentFontChangeStrikeOut;
			using CControl::getOnParentFontChangeWidth;
			using CControl::getOnParentFontChangeCharSet;
			using CControl::getOnParentFontChangeQuality;
			using CControl::getOnParentFontChangePitchAndFamily;
			using CControl::getOnParentFontChangeOrientation;
			using CControl::getOnParentFontChangeDistance;
			using CControl::getOnParentFontChangeShadow;
			using CControl::getOnParentFontChangeShadowShift;
			using CControl::getOnParentFontChangeShadowBlur;
			using CControl::getOnParentFontChangeShadowColor;
			using CControl::getOnParentFontChangeColor;
			using CControl::getOnParentFontChangeInterpolate;
			using CControl::getOnParentFontBeginChange;
			using CControl::getOnParentFontEndChange;
			using CControl::getOnParentFontChangeSize;
			using CControl::getOnParentFontChangeStyle;
			using CControl::getOnFontChangeName;
			using CControl::getOnFontChangeHeight;
			using CControl::getOnFontChangeWeight;
			using CControl::getOnFontChangeItalic;
			using CControl::getOnFontChangeUnderline;
			using CControl::getOnFontChangeStrikeOut;
			using CControl::getOnFontChangeWidth;
			using CControl::getOnFontChangeCharSet;
			using CControl::getOnFontChangeQuality;
			using CControl::getOnFontChangePitchAndFamily;
			using CControl::getOnFontChangeOrientation;
			using CControl::getOnFontChangeDistance;
			using CControl::getOnFontChangeShadow;
			using CControl::getOnFontChangeShadowShift;
			using CControl::getOnFontChangeShadowBlur;
			using CControl::getOnFontChangeShadowColor;
			using CControl::getOnFontChangeColor;
			using CControl::getOnFontChangeInterpolate;
			using CControl::getOnFontBeginChange;
			using CControl::getOnFontEndChange;
			using CControl::getOnFontChangeSize;
			using CControl::getOnFontChangeStyle;
			using CControl::getOnMouseHover;
			using CControl::getOnMouseLeave;
			using CControl::getOnChangeParentStyle;
			using CControl::getOnChangeStyle;
			using CControl::getOnShow;
			using CControl::getOnBeforeHide;
			using CControl::getOnHide;
			using CControl::getOnEnable;
			using CControl::getOnDisable;
			using CControl::getOnAttachControl;
			using CControl::getOnBeforeDetachControl;
			using CControl::getOnDetachControl;
			using CControl::getOnPaint;
			using CControl::getOnParentResize;
			using CControl::getOnParentMove;
			using CControl::getOnBeforeResize;
			using CControl::getOnResize;
			using CControl::getOnBeforeMove;
			using CControl::getOnMove;
			using CControl::getOnChildControlResize;
			using CControl::getOnChildControlMove;
			using CControl::getOnBeforeDetachFromControl;
			using CControl::getOnDetachFromControl;
			using CControl::getOnAttachToControl;
			using CControl::setOnMouseMove;
			using CControl::setOnLeftMouseButtonDown;
			using CControl::setOnLeftMouseButtonUp;
			using CControl::setOnLeftMouseButtonDoubleClick;
			using CControl::setOnRightMouseButtonDown;
			using CControl::setOnRightMouseButtonUp;
			using CControl::setOnRightMouseButtonDoubleClick;
			using CControl::setOnMiddleMouseButtonDown;
			using CControl::setOnMiddleMouseButtonUp;
			using CControl::setOnMiddleMouseButtonDoubleClick;
			using CControl::setOnMouseVerticalWheel;
			using CControl::setOnMouseHorizontalWheel;
			using CControl::setOnChangeUseParentFont;
			using CControl::setOnParentFontChangeName;
			using CControl::setOnParentFontChangeHeight;
			using CControl::setOnParentFontChangeWeight;
			using CControl::setOnParentFontChangeItalic;
			using CControl::setOnParentFontChangeUnderline;
			using CControl::setOnParentFontChangeStrikeOut;
			using CControl::setOnParentFontChangeWidth;
			using CControl::setOnParentFontChangeCharSet;
			using CControl::setOnParentFontChangeQuality;
			using CControl::setOnParentFontChangePitchAndFamily;
			using CControl::setOnParentFontChangeOrientation;
			using CControl::setOnParentFontChangeDistance;
			using CControl::setOnParentFontChangeShadow;
			using CControl::setOnParentFontChangeShadowShift;
			using CControl::setOnParentFontChangeShadowBlur;
			using CControl::setOnParentFontChangeShadowColor;
			using CControl::setOnParentFontChangeColor;
			using CControl::setOnParentFontChangeInterpolate;
			using CControl::setOnParentFontBeginChange;
			using CControl::setOnParentFontEndChange;
			using CControl::setOnParentFontChangeSize;
			using CControl::setOnParentFontChangeStyle;
			using CControl::setOnFontChangeName;
			using CControl::setOnFontChangeHeight;
			using CControl::setOnFontChangeWeight;
			using CControl::setOnFontChangeItalic;
			using CControl::setOnFontChangeUnderline;
			using CControl::setOnFontChangeStrikeOut;
			using CControl::setOnFontChangeWidth;
			using CControl::setOnFontChangeCharSet;
			using CControl::setOnFontChangeQuality;
			using CControl::setOnFontChangePitchAndFamily;
			using CControl::setOnFontChangeOrientation;
			using CControl::setOnFontChangeDistance;
			using CControl::setOnFontChangeShadow;
			using CControl::setOnFontChangeShadowShift;
			using CControl::setOnFontChangeShadowBlur;
			using CControl::setOnFontChangeShadowColor;
			using CControl::setOnFontChangeColor;
			using CControl::setOnFontChangeInterpolate;
			using CControl::setOnFontBeginChange;
			using CControl::setOnFontEndChange;
			using CControl::setOnFontChangeSize;
			using CControl::setOnFontChangeStyle;
			using CControl::setOnMouseHover;
			using CControl::setOnMouseLeave;
			using CControl::setOnChangeParentStyle;
			using CControl::setOnChangeStyle;
			using CControl::setOnShow;
			using CControl::setOnBeforeHide;
			using CControl::setOnHide;
			using CControl::setOnEnable;
			using CControl::setOnDisable;
			using CControl::setOnAttachControl;
			using CControl::setOnBeforeDetachControl;
			using CControl::setOnDetachControl;
			using CControl::setOnPaint;
			using CControl::setOnParentResize;
			using CControl::setOnParentMove;
			using CControl::setOnBeforeResize;
			using CControl::setOnResize;
			using CControl::setOnBeforeMove;
			using CControl::setOnMove;
			using CControl::setOnChildControlResize;
			using CControl::setOnChildControlMove;
			using CControl::setOnBeforeDetachFromControl;
			using CControl::setOnDetachFromControl;
			using CControl::setOnAttachToControl;
			using CControl::getControlAtPosition;
			using CControl::getControlStyle;
			using CControl::getStyle;
			using CControl::getUseStyle;
			using CControl::getConstraints;
			using CControl::getMinConstraints;
			using CControl::getMaxConstraints;
			using CControl::getMinWidth;
			using CControl::getMinHeight;
			using CControl::getMaxWidth;
			using CControl::getMaxHeight;
			using CControl::getControlFont;
			using CControl::getParentFont;
			using CControl::getFont;
			using CControl::getUseParentFont;
			using CControl::getZIndex;
			using CControl::setParent;
			using CControl::setEnabled;
			using CControl::setVisible;
			using CControl::setAlign;
			using CControl::setStyle;
			using CControl::setUseStyle;
			using CControl::setConstraints;
			using CControl::setMinConstraints;
			using CControl::setMinWidth;
			using CControl::setMinHeight;
			using CControl::setMaxWidth;
			using CControl::setMaxHeight;
			using CControl::setControlFont;
			using CControl::setFont;
			using CControl::setUseParentFont;
			using CControl::setRect;
			using CControl::setPosition;
			using CControl::setLeft;
			using CControl::setTop;
			using CControl::setSize;
			using CControl::setWidth;
			using CControl::setHeight;
			using CControl::setCursor;
			using CControl::setZIndex;
			using CControl::AddControl;
			using CControl::InsertControl;
			using CControl::DeleteControl;
			using CControl::DetachControl;
			using CControl::DeleteControls;
		};
	}
}