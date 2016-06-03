// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Control.h"
#include "..\..\..\Components\ImageList\ImageList.h"
#include "..\..\..\Image.h"

namespace licui
{
	namespace application
	{
		class CButton :public CControl
		{
		public:
			enum STATE
			{
				stNormal,
				stNormalHovered,
				stFocused,
				stFocusedHovered,
				stActive,
				stDisabled
			};
			enum IMAGE_ALIGN
			{
				ialLeft,
				ialRight
			};
			typedef void(*FOnClick)(CButton *sender, void *param);
		private:
			struct SETTING :IImage::GRADIENT
			{
				CImageList *ImageList;
				int ImageIndex;
				APP_COLOR TextColor;
				APP_COLOR ShadowColor;
				APP_COLOR BorderOuterColor;
				APP_COLOR BorderInnerColor;
				APP_COLOR BackgroundColor; // Used if no gardient points exists
			};

			SETTING m_aStates[stDisabled + 1];
			String m_sCaption;
			TEXT_ALIGN m_eCaptionHorizontalAlign;
			VERTICAL_ALIGN m_eCaptionVerticalAlign;
			IMAGE_ALIGN m_eImageAlign;
			math::RECTANGLE<size_t> m_sImageMargin;
			size_t m_iBorderRadius;
			size_t m_iBorderOuterWidth;
			size_t m_iBorderInnerWidth;
			size_t m_iBorderAntiAliazing;
			FOnClick m_fOnClick;
			bool m_bIsActive;

			void InitStates();
			bool SearchImage(APP_IMAGE **image, APP_RECT &rect);
			void PaintBorderOuter(APP_RECT clip, APP_RECT &rect);
			void PaintBorderInner(APP_RECT clip, APP_RECT &rect);
			void PaintBackground(APP_RECT clip, APP_RECT &rect);
			void PaintCaption(APP_RECT clip, const APP_RECT &rect);
			void PaintImage(APP_RECT clip, const APP_RECT &rect);
		protected:
			bool UpdateFromStyle() override;

			void NotifyOnBeforeDetachComponentFromForm(CComponent *component) override;
			void NotifyOnUpdateComponent(CComponent *component) override;

			bool NotifyOnKeyDown(const IWindow::KEY key) override;
			bool NotifyOnKeyUp(const IWindow::KEY key) override;
			bool NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;

			void NotifyOnKillCaptureMouse() override;
			void NotifyOnSetCaptureMouse() override;
			void NotifyOnMouseHover() override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillFocus() override;
			void NotifyOnSetFocus(CControl *old) override;
			void NotifyOnResetFocus() override;
			void NotifyOnPaint(APP_RECT clip) override;

			virtual void NotifyOnClick();
		public:
			virtual STATE getState() const;
			virtual String getCaption() const;
			virtual TEXT_ALIGN getCaptionHorizontalAlign() const;
			virtual VERTICAL_ALIGN getCaptionVerticalAlign() const;
			virtual IMAGE_ALIGN getImageAlign() const;
			virtual math::RECTANGLE<size_t> getImageMargin() const;
			virtual size_t getImageMarginLeft() const;
			virtual size_t getImageMarginTop() const;
			virtual size_t getImageMarginRight() const;
			virtual size_t getImageMarginBottom() const;
			virtual size_t getBorderRadius() const;
			virtual size_t getBorderOuterWidth() const;
			virtual size_t getBorderInnerWidth() const;
			virtual size_t getBorderAntiAliazing() const;
			virtual CImageList *getImageList(const STATE state);
			virtual int getImageIndex(const STATE state) const;
			virtual APP_COLOR getTextColor(const STATE state) const;
			virtual APP_COLOR getShadowColor(const STATE state) const;
			virtual APP_COLOR getBorderOuterColor(const STATE state) const;
			virtual APP_COLOR getBorderInnerColor(const STATE state) const;
			virtual APP_COLOR getBackgroundColor(const STATE state) const;
			virtual IImage::GRADIENT_TYPE getGradientType(const STATE state) const;
			virtual size_t getGradientPointCount(const STATE state) const;
			virtual double getGradientPointPosition(const STATE state, const size_t index) const;
			virtual APP_COLOR getGradientPointColor(const STATE state, const size_t index) const;
			virtual FOnClick getOnClick() const;

			virtual CButton *setCaption(const String &value);
			virtual CButton *setCaptionHorizontalAlign(const TEXT_ALIGN value);
			virtual CButton *setCaptionVerticalAlign(const VERTICAL_ALIGN value);
			virtual CButton *setImageAlign(const IMAGE_ALIGN value);
			virtual CButton *setImageMargin(const math::RECTANGLE<size_t> &value);
			virtual CButton *setImageMarginLeft(const size_t value);
			virtual CButton *setImageMarginTop(const size_t value);
			virtual CButton *setImageMarginRight(const size_t value);
			virtual CButton *setImageMarginBottom(const size_t value);
			virtual CButton *setBorderRadius(const size_t value);
			virtual CButton *setBorderOuterWidth(const size_t value);
			virtual CButton *setBorderInnerWidth(const size_t value);
			virtual CButton *setBorderAntiAliazing(const size_t value);
			virtual CButton *setImageList(CImageList *value);
			virtual CButton *setImageList(const STATE state, CImageList *value);
			virtual CButton *setImageIndex(const int value);
			virtual CButton *setImageIndex(const STATE state, const int value);
			virtual CButton *setTextColor(const APP_COLOR &value);
			virtual CButton *setTextColor(const STATE state, const APP_COLOR &value);
			virtual CButton *setShadowColor(const APP_COLOR &value);
			virtual CButton *setShadowColor(const STATE state, const APP_COLOR &value);
			virtual CButton *setBorderOuterColor(const APP_COLOR &value);
			virtual CButton *setBorderOuterColor(const STATE state, const APP_COLOR &value);
			virtual CButton *setBorderInnerColor(const APP_COLOR &value);
			virtual CButton *setBorderInnerColor(const STATE state, const APP_COLOR &value);
			virtual CButton *setBackgroundColor(const APP_COLOR &value);
			virtual CButton *setBackgroundColor(const STATE state, const APP_COLOR &value);
			virtual CButton *setGradientType(const IImage::GRADIENT_TYPE value);
			virtual CButton *setGradientType(const STATE state, const IImage::GRADIENT_TYPE value);
			virtual CButton *setGradientPointCount(const size_t value);
			virtual CButton *setGradientPointCount(const STATE state, const size_t value);
			virtual CButton *setGradientPointPosition(const size_t index, const double value);
			virtual CButton *setGradientPointPosition(const STATE state, const size_t index, const double value);
			virtual CButton *setGradientPointColor(const size_t index, const APP_COLOR &value);
			virtual CButton *setGradientPointColor(const STATE state, const size_t index, const APP_COLOR &value);
			virtual CButton *setGradientPoints(const size_t count, IImage::GRADIENT_POINT *points);
			virtual CButton *setGradientPoints(const STATE state, const size_t count, IImage::GRADIENT_POINT *points);
			virtual CButton *setOnClick(FOnClick value);

			CButton();
			CButton(CForm *form);
			CButton(CControl *parent);
		public:
			using CControl::getOnKeyDown;
			using CControl::getOnKeyUp;
			using CControl::getOnChar;
			using CControl::getOnDeadChar;
			using CControl::getOnSysKeyDown;
			using CControl::getOnSysKeyUp;
			using CControl::getOnSysChar;
			using CControl::getOnSysDeadChar;
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
			using CControl::getOnKillFocus;
			using CControl::getOnSetFocus;
			using CControl::getOnResetFocus;
			using CControl::getOnKillCaptureMouse;
			using CControl::getOnSetCaptureMouse;
			using CControl::getOnChangeParentStyle;
			using CControl::getOnChangeStyle;
			using CControl::getOnShow;
			using CControl::getOnBeforeHide;
			using CControl::getOnHide;
			using CControl::getOnEnable;
			using CControl::getOnDisable;
			using CControl::getOnPaint;
			using CControl::getOnParentResize;
			using CControl::getOnParentMove;
			using CControl::getOnBeforeResize;
			using CControl::getOnResize;
			using CControl::getOnBeforeMove;
			using CControl::getOnMove;
			using CControl::getOnBeforeDetachFromControl;
			using CControl::getOnDetachFromControl;
			using CControl::getOnAttachToControl;
			using CControl::setOnKeyDown;
			using CControl::setOnKeyUp;
			using CControl::setOnChar;
			using CControl::setOnDeadChar;
			using CControl::setOnSysKeyDown;
			using CControl::setOnSysKeyUp;
			using CControl::setOnSysChar;
			using CControl::setOnSysDeadChar;
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
			using CControl::setOnKillFocus;
			using CControl::setOnSetFocus;
			using CControl::setOnResetFocus;
			using CControl::setOnKillCaptureMouse;
			using CControl::setOnSetCaptureMouse;
			using CControl::setOnChangeParentStyle;
			using CControl::setOnChangeStyle;
			using CControl::setOnShow;
			using CControl::setOnBeforeHide;
			using CControl::setOnHide;
			using CControl::setOnEnable;
			using CControl::setOnDisable;
			using CControl::setOnPaint;
			using CControl::setOnParentResize;
			using CControl::setOnParentMove;
			using CControl::setOnBeforeResize;
			using CControl::setOnResize;
			using CControl::setOnBeforeMove;
			using CControl::setOnMove;
			using CControl::setOnBeforeDetachFromControl;
			using CControl::setOnDetachFromControl;
			using CControl::setOnAttachToControl;
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