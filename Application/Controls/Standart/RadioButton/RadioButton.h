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
		class CRadioButton :public CControl
		{
		public:
			typedef void(*FOnChange)(CRadioButton *sender, void *param);
		private:
			bool m_bAutoSize;
			bool m_bChecked;
			String m_sCaption;
			math::RECTANGLE<size_t> m_sMarginImage;
			math::RECTANGLE<size_t> m_sMarginCaption;
			size_t m_iGroupIndex;
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
			void UpdateGroup();
			bool UpdateState();
			void SelectColors(APP_COLOR &text, APP_COLOR &shadow);
			void Paint(APP_RECT clip);
		protected:
			bool UpdateFromStyle() override;

			void NotifyOnAttachToForm() override;

			bool NotifyOnKeyDown(const IWindow::KEY key) override;
			bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;

			void NotifyOnMouseHover() override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillFocus() override;
			void NotifyOnSetFocus(CControl *old) override;
			void NotifyOnResetFocus() override;
			void NotifyOnPaint(APP_RECT clip) override;
			void NotifyOnAttachToControl(CControl *control) override;

			virtual void NotifyOnChange();
		public:
			void UpdateRect() override;
			CControl *setRect(APP_RECT value) override;

			CRadioButton();
			CRadioButton(CForm *form);
			CRadioButton(CControl *parent);

			virtual bool getAutoSize() const;
			virtual bool getChecked() const;
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
			virtual size_t getGroupIndex() const;
			virtual APP_COLOR getDisabledTextColor() const;
			virtual APP_COLOR getDisabledShadowColor() const;
			virtual APP_COLOR getFocusedTextColor() const;
			virtual APP_COLOR getFocusedShadowColor() const;
			virtual APP_COLOR getHoveredTextColor() const;
			virtual APP_COLOR getHoveredShadowColor() const;
			virtual APP_COLOR getFocusedHoveredTextColor() const;
			virtual APP_COLOR getFocusedHoveredShadowColor() const;
			virtual FOnChange getOnChange() const;

			virtual CRadioButton *setAutoSize(const bool value);
			virtual CRadioButton *setChecked(const bool value);
			virtual CRadioButton *setCaption(const String &value);
			virtual CRadioButton *setMarginImage(const math::RECTANGLE<size_t> &value);
			virtual CRadioButton *setMarginImageLeft(const size_t value);
			virtual CRadioButton *setMarginImageTop(const size_t value);
			virtual CRadioButton *setMarginImageRight(const size_t value);
			virtual CRadioButton *setMarginImageBottom(const size_t value);
			virtual CRadioButton *setMarginCaption(const math::RECTANGLE<size_t> &value);
			virtual CRadioButton *setMarginCaptionLeft(const size_t value);
			virtual CRadioButton *setMarginCaptionTop(const size_t value);
			virtual CRadioButton *setMarginCaptionRight(const size_t value);
			virtual CRadioButton *setMarginCaptionBottom(const size_t value);
			virtual CRadioButton *setGroupIndex(const size_t value);
			virtual CRadioButton *setDisabledTextColor(const APP_COLOR &value);
			virtual CRadioButton *setDisabledShadowColor(const APP_COLOR &value);
			virtual CRadioButton *setFocusedTextColor(const APP_COLOR &value);
			virtual CRadioButton *setFocusedShadowColor(const APP_COLOR &value);
			virtual CRadioButton *setHoveredTextColor(const APP_COLOR &value);
			virtual CRadioButton *setHoveredShadowColor(const APP_COLOR &value);
			virtual CRadioButton *setFocusedHoveredTextColor(const APP_COLOR &value);
			virtual CRadioButton *setFocusedHoveredShadowColor(const APP_COLOR &value);
			virtual CRadioButton *setOnChange(FOnChange value);
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