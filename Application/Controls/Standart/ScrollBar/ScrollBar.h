// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Control.h"
#include "..\..\..\Image.h"

namespace licui
{
	namespace application
	{
		class CScrollBar :public CControl
		{
		public:
			enum TYPE
			{
				sbVertical,
				sbHorizontal
			};
			enum STATE
			{
				stNormal, // Normal enabled state
				stActive, // Mouse was down over any element
				stHovered, // Mouse is over scrollbar
				stDisabled // Scrollbar is disabled
			};
			enum ELEMENT_STATE
			{
				estNormal, // Normal enabled state
				estActive, // Mouse was down over element
				estHovered, // Mouse over scrollbar but not over element
				estOver, // Mouse over element
				estDisabled // Scrollbar is disabled
			};
			enum ELEMENT_TYPE
			{
				etStartArrow,
				etEndArrow,
				etScroller
			};
			typedef void(*FOnScroll)(CScrollBar *sender, void *param);
		private:
			struct ELEMENT_SETTINGS
			{
				size_t BorderWidth;
				size_t BorderRadius;
				size_t BorderAntiAliazing;
				struct :IImage::GRADIENT
				{
					APP_COLOR BackgroundColor;
					APP_COLOR BorderColor;
				} State[estDisabled + 1];
			};
			struct BACKGROUND_STATE :IImage::GRADIENT
			{
				APP_COLOR BackgroundColor;
				APP_COLOR BorderColor;
				APP_COLOR BoxShadowColor;
			};

			TYPE m_eType;
			int m_iMin;
			int m_iMax;
			int m_iScroll;
			size_t m_iPageSize; // Change value by down not on scroller
			size_t m_iDeltaArrow; // Change value by arrows
			size_t m_iDeltaScroll; // Change value by scroll
			size_t m_iScrollerSize; // 0 for auto size
			size_t m_iBorderWidth;
			bool m_bBoxShadow;
			APP_POINT m_sBoxShadowShift;
			size_t m_iBoxShadowRadius;
			FOnScroll m_fOnScroll;
			ELEMENT_SETTINGS m_aElements[etScroller + 1];
			BACKGROUND_STATE m_aBackground[stDisabled + 1];

			unsigned int m_hTimer;
			bool m_bMouseOverStartArrow;
			bool m_bMouseOverEndArrow;
			bool m_bMouseOverScroller;
			bool m_bMouseDownOnStartArrow;
			bool m_bMouseDownOnEndArrow;
			bool m_bMouseDownOnScroller;
			bool m_bMouseDownBeforeScroller;
			bool m_bMouseDownAfterScroller;
			int m_iMouseDownScrollDelta;
			bool m_bCancellingDown;

			bool SearchElementImage(const ELEMENT_TYPE type, APP_IMAGE **image, APP_RECT &rect, const bool ignore_state);
			APP_RECT CalculateStartArrowRect();
			APP_RECT CalculateEndArrowRect();
			APP_RECT CalculateScrollerRect();
			APP_RECT CalculateBeforeScrollerRect();
			APP_RECT CalculateAfterScrollerRect();
			static void TimerCallback(void *param);
			void InitGradients();
			int MouseToScroll(const int x, const int y);
			String StateToString(const STATE state);
			String ElementStateToString(const ELEMENT_STATE state);

			void PaintBackground(APP_RECT clip); // + border, + shadow
			void PaintElement(const ELEMENT_TYPE type, APP_RECT clip, APP_RECT rect);

			bool ProcessMoveScroller(const int x, const int y);
			bool ProcessMoveOverStartArrow(const int x, const int y);
			bool ProcessMoveOverEndArrow(const int x, const int y);
			bool ProcessMoveOverScroller(const int x, const int y);
			void ProcessMoveOverOther();
			bool ProcessCancelDown();
			bool ProcessDownOnStartArrow(const int x, const int y);
			bool ProcessDownOnEndArrow(const int x, const int y);
			bool ProcessDownOnScroller(const int x, const int y);
			bool ProcessDownBeforeScroller(const int x, const int y);
			bool ProcessDownAfterScroller(const int x, const int y);
			void ProcessWheel(const int x, const int y, const int delta);
		protected:
			bool UpdateFromStyle() override;

			void NotifyOnDetachFromForm() override;

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

			void NotifyOnMouseHover() override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillCaptureMouse() override;
			void NotifyOnSetCaptureMouse() override;
			void NotifyOnPaint(APP_RECT clip) override;

			virtual void NotifyOnScroll();
		public:
			APP_RECT getRenderRect() override;

			virtual TYPE getType() const;
			virtual STATE getState() const;
			virtual ELEMENT_STATE getElementState(const ELEMENT_TYPE type) const;
			virtual int getMin() const;
			virtual int getMax() const;
			virtual int getScroll() const;
			virtual size_t getPageSize() const;
			virtual size_t getDeltaArrow() const;
			virtual size_t getDeltaScroll() const;
			virtual size_t getScrollerSize() const;
			virtual size_t getBorderWidth() const;
			virtual bool getBoxShadow() const;
			virtual APP_POINT getBoxShadowShift() const;
			virtual int getBoxShadowShiftX() const;
			virtual int getBoxShadowShiftY() const;
			virtual size_t getBoxShadowRadius() const;
			virtual FOnScroll getOnScroll() const;
			virtual APP_COLOR getBackgroundColor(const STATE state) const;
			virtual APP_COLOR getBorderColor(const STATE state) const;
			virtual APP_COLOR getBoxShadowColor(const STATE state) const;
			virtual IImage::GRADIENT_TYPE getGradientType(const STATE state) const;
			virtual size_t getGradientPointCount(const STATE state) const;
			virtual double getGradientPointPosition(const STATE state, const size_t index) const;
			virtual APP_COLOR getGradientPointColor(const STATE state, const size_t index) const;
			virtual size_t getElementBorderWidth(const ELEMENT_TYPE element) const;
			virtual size_t getElementBorderRadius(const ELEMENT_TYPE element) const;
			virtual size_t getElementBorderAntiAliazing(const ELEMENT_TYPE element) const;
			virtual APP_COLOR getElementBackgroundColor(const ELEMENT_TYPE element, const ELEMENT_STATE state) const;
			virtual APP_COLOR getElementBorderColor(const ELEMENT_TYPE element, const ELEMENT_STATE state) const;
			virtual IImage::GRADIENT_TYPE getElementGradientType(const ELEMENT_TYPE element, const ELEMENT_STATE state) const;
			virtual size_t getElementGradientPointCount(const ELEMENT_TYPE element, const ELEMENT_STATE state) const;
			virtual double getElementGradientPointPosition(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index) const;
			virtual APP_COLOR getElementGradientPointColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index) const;

			virtual CScrollBar *setType(const TYPE value);
			virtual CScrollBar *setMin(const int value);
			virtual CScrollBar *setMax(const int value);
			virtual CScrollBar *setScroll(int value);
			virtual CScrollBar *setPageSize(size_t value);
			virtual CScrollBar *setDeltaArrow(size_t value);
			virtual CScrollBar *setDeltaScroll(size_t value);
			virtual CScrollBar *setScrollerSize(const size_t value);
			virtual CScrollBar *setBorderWidth(const size_t value);
			virtual CScrollBar *setBoxShadow(const bool value);
			virtual CScrollBar *setBoxShadowShift(const APP_POINT &value);
			virtual CScrollBar *setBoxShadowShiftX(const int value);
			virtual CScrollBar *setBoxShadowShiftY(const int value);
			virtual CScrollBar *setBoxShadowRadius(const size_t value);
			virtual CScrollBar *setOnScroll(FOnScroll value);
			virtual CScrollBar *setBackgroundColor(const STATE state, const APP_COLOR &value);
			virtual CScrollBar *setBorderColor(const STATE state, const APP_COLOR &value);
			virtual CScrollBar *setBoxShadowColor(const STATE state, const APP_COLOR &value);
			virtual CScrollBar *setGradientType(const STATE state, const IImage::GRADIENT_TYPE value);
			virtual CScrollBar *setGradientPointCount(const STATE state, const size_t value);
			virtual CScrollBar *setGradientPointPosition(const STATE state, const size_t index, const double value);
			virtual CScrollBar *setGradientPointColor(const STATE state, const size_t index, const APP_COLOR &value);
			virtual CScrollBar *setGradientPoints(const STATE state, const size_t count, IImage::GRADIENT_POINT *points);
			virtual CScrollBar *setElementBorderWidth(const ELEMENT_TYPE element, const size_t value);
			virtual CScrollBar *setElementBorderRadius(const ELEMENT_TYPE element, const size_t value);
			virtual CScrollBar *setElementBorderAntiAliazing(const ELEMENT_TYPE element, const size_t value);
			virtual CScrollBar *setElementBackgroundColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const APP_COLOR &value);
			virtual CScrollBar *setElementBorderColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const APP_COLOR &value);
			virtual CScrollBar *setElementGradientType(const ELEMENT_TYPE element, const ELEMENT_STATE state, const IImage::GRADIENT_TYPE value);
			virtual CScrollBar *setElementGradientPointCount(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t value);
			virtual CScrollBar *setElementGradientPointPosition(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index, const double value);
			virtual CScrollBar *setElementGradientPointColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index, const APP_COLOR &value);
			virtual CScrollBar *setElementGradientPoints(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t count, IImage::GRADIENT_POINT *points);

			CScrollBar();
			CScrollBar(CForm *form);
			CScrollBar(CControl *parent);
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
			using CControl::getOnMouseHover;
			using CControl::getOnMouseLeave;
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
			using CControl::setOnMouseHover;
			using CControl::setOnMouseLeave;
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
			using CControl::setRect;
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