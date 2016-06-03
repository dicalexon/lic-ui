// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\..\Strings\Strings.h"
#include "..\..\..\Types.h"
#include "..\..\..\Control.h"

namespace licui
{
	namespace application
	{
		class CLabel :public CControl
		{
		private:
			bool m_bAutoSize;
			String m_sCaption;
			size_t m_iAntiAliazing;
			TEXT_ALIGN m_eHotizontalAlign;
			VERTICAL_ALIGN m_eVerticalAlign;
			math::POINT<double> m_dScale;
		protected:
			void NotifyOnPaint(APP_RECT clip) override;
		public:
			virtual bool getAutoSize() const;
			virtual String getCaption() const;
			virtual size_t getAntiAliazing() const;
			virtual TEXT_ALIGN getHorizontalAlign() const;
			virtual VERTICAL_ALIGN getVerticalAlign() const;
			virtual math::POINT<double> getScale() const;
			virtual double getScaleX() const;
			virtual double getScaleY() const;

			virtual CLabel *setAutoSize(const bool value);
			virtual CLabel *setCaption(const String &value);
			virtual CLabel *setAntiAliazing(size_t value);
			virtual CLabel *setHorizontalAlign(const TEXT_ALIGN value);
			virtual CLabel *setVerticalAlign(const VERTICAL_ALIGN value);
			virtual CLabel *setScale(const math::POINT<double> &value);
			virtual CLabel *setScaleX(const double value);
			virtual CLabel *setScaleY(const double value);

			CLabel();
			CLabel(CControl *parent);
			CLabel(CForm *form);

			void UpdateRect() override;
		public:
			CControl *setAlign(const ALIGN value) override;
			CControl *setRect(APP_RECT value) override;
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
			using CControl::getOnPaint;
			using CControl::getOnParentResize;
			using CControl::getOnParentMove;
			using CControl::getOnBeforeResize;
			using CControl::getOnResize;
			using CControl::getOnBeforeMove;
			using CControl::getOnMove;
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
			using CControl::setOnPaint;
			using CControl::setOnParentResize;
			using CControl::setOnParentMove;
			using CControl::setOnBeforeResize;
			using CControl::setOnResize;
			using CControl::setOnBeforeMove;
			using CControl::setOnMove;
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
			using CControl::setPosition;
			using CControl::setLeft;
			using CControl::setTop;
			using CControl::setSize;
			using CControl::setWidth;
			using CControl::setHeight;
			using CControl::setCursor;
			using CControl::setZIndex;
		};
	}
}