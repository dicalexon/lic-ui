// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Control.h"

namespace licui
{
	namespace application
	{
		class CCheckBox :public CControl
		{
		public:
			enum STATE
			{
				cbsUnchecked,
				cbsChecked,
				cbsGrayed
			};
			typedef void(*FOnChange)(CCheckBox *sender, void *param);
		private:
			bool m_bAutoSize;
			STATE m_eState;
			String m_sCaption;
			math::RECTANGLE<size_t> m_sMarginImage;
			math::RECTANGLE<size_t> m_sMarginCaption;
			APP_COLOR m_sDisabledTextColor; // If alpha = 0, not used
			APP_COLOR m_sDisabledShadowColor;
			APP_COLOR m_sFocusedTextColor;
			APP_COLOR m_sFocusedShadowColor;
			APP_COLOR m_sHoveredTextColor;
			APP_COLOR m_sHoveredShadowColor;
			APP_COLOR m_sFocusedHoveredTextColor;
			APP_COLOR m_sFocusedHoveredShadowColor;
			FOnChange m_fOnChange;

			bool SearchImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state);
			APP_RECT CalculateImageRect();
			APP_RECT CalculateCaptionRect();
			math::POINT<size_t> CalculateSize();
			void SelectColors(APP_COLOR &text, APP_COLOR &shadow);
			void Paint(APP_RECT clip);
		protected:
			bool UpdateFromStyle() override;

			bool NotifyOnKeyDown(const IWindow::KEY key) override;
			bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;

			void NotifyOnMouseHover() override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillFocus() override;
			void NotifyOnSetFocus(CControl *old) override;
			void NotifyOnResetFocus() override;
			void NotifyOnPaint(APP_RECT clip) override;

			virtual void NotifyOnChange();
		public:
			void UpdateRect() override;
			CControl *setRect(APP_RECT value) override;

			CCheckBox();
			CCheckBox(CForm *form);
			CCheckBox(CControl *parent);

			virtual bool getAutoSize() const;
			virtual STATE getState() const;
			virtual String getCaption() const;
			virtual math::RECTANGLE<size_t> getMarginImage() const;
			virtual size_t getMarginImageLeft() const;
			virtual size_t getMarginImageTop() const;
			virtual size_t getMarginImageRight() const;
			virtual size_t getMarginImageBottom() const;
			virtual math::RECTANGLE<size_t> getMarginCaption() const;
			virtual size_t getMarginCaptionLeft() const;
			virtual size_t getMarginCaptionTop() const;
			virtual size_t getMarginCaptionRight() const;
			virtual size_t getMarginCaptionBottom() const;
			virtual APP_COLOR getDisabledTextColor() const;
			virtual APP_COLOR getDisabledShadowColor() const;
			virtual APP_COLOR getFocusedTextColor() const;
			virtual APP_COLOR getFocusedShadowColor() const;
			virtual APP_COLOR getHoveredTextColor() const;
			virtual APP_COLOR getHoveredShadowColor() const;
			virtual APP_COLOR getFocusedHoveredTextColor() const;
			virtual APP_COLOR getFocusedHoveredShadowColor() const;
			virtual FOnChange getOnChange() const;

			virtual CCheckBox *setAutoSize(const bool value);
			virtual CCheckBox *setState(const STATE value);
			virtual CCheckBox *setCaption(const String &value);
			virtual CCheckBox *setMarginImage(const math::RECTANGLE<size_t> &value);
			virtual CCheckBox *setMarginImageLeft(const size_t value);
			virtual CCheckBox *setMarginImageTop(const size_t value);
			virtual CCheckBox *setMarginImageRight(const size_t value);
			virtual CCheckBox *setMarginImageBottom(const size_t value);
			virtual CCheckBox *setMarginCaption(const math::RECTANGLE<size_t> &value);
			virtual CCheckBox *setMarginCaptionLeft(const size_t value);
			virtual CCheckBox *setMarginCaptionTop(const size_t value);
			virtual CCheckBox *setMarginCaptionRight(const size_t value);
			virtual CCheckBox *setMarginCaptionBottom(const size_t value);
			virtual CCheckBox *setDisabledTextColor(const APP_COLOR &value);
			virtual CCheckBox *setDisabledShadowColor(const APP_COLOR &value);
			virtual CCheckBox *setFocusedTextColor(const APP_COLOR &value);
			virtual CCheckBox *setFocusedShadowColor(const APP_COLOR &value);
			virtual CCheckBox *setHoveredTextColor(const APP_COLOR &value);
			virtual CCheckBox *setHoveredShadowColor(const APP_COLOR &value);
			virtual CCheckBox *setFocusedHoveredTextColor(const APP_COLOR &value);
			virtual CCheckBox *setFocusedHoveredShadowColor(const APP_COLOR &value);
			virtual CCheckBox *setOnChange(FOnChange value);
		public:
			using CControl::getOnKeyDown;
			using CControl::getOnKeyUp;
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
			using CControl::getOnKillFocus;
			using CControl::getOnSetFocus;
			using CControl::getOnResetFocus;
			using CControl::getOnChangeParentStyle;
			using CControl::getOnChangeStyle;
			using CControl::getOnShow;
			using CControl::getOnBeforeHide;
			using CControl::getOnHide;
			using CControl::getOnEnable;
			using CControl::getOnDisable;
			using CControl::getOnPaint;
			using CControl::getOnBeforeResize;
			using CControl::getOnResize;
			using CControl::getOnBeforeMove;
			using CControl::getOnMove;
			using CControl::setOnKeyDown;
			using CControl::setOnKeyUp;
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
			using CControl::setOnKillFocus;
			using CControl::setOnSetFocus;
			using CControl::setOnResetFocus;
			using CControl::setOnChangeParentStyle;
			using CControl::setOnChangeStyle;
			using CControl::setOnShow;
			using CControl::setOnBeforeHide;
			using CControl::setOnHide;
			using CControl::setOnEnable;
			using CControl::setOnDisable;
			using CControl::setOnPaint;
			using CControl::setOnBeforeResize;
			using CControl::setOnResize;
			using CControl::setOnBeforeMove;
			using CControl::setOnMove;
			using CControl::getTabStop;
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
			using CControl::setTabStop;
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
			using CControl::setFocus;
			using CControl::setRect;
			using CControl::setPosition;
			using CControl::setLeft;
			using CControl::setTop;
			using CControl::setSize;
			using CControl::setWidth;
			using CControl::setHeight;
			using CControl::setTabOrder;
			using CControl::setCursor;
			using CControl::setZIndex;
		};
	}
}