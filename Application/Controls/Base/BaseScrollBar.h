// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\Types.h"
#include "..\..\Image.h"

namespace licui
{
	namespace application
	{
		class CBaseScrollBar
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
		private:
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
			bool m_bHovered;

			void InitGradients();
			bool SearchElementImage(const ELEMENT_TYPE type, APP_IMAGE **image, APP_RECT &rect, const bool ignore_state);
			APP_RECT CalculateStartArrowRect();
			APP_RECT CalculateEndArrowRect();
			APP_RECT CalculateScrollerRect();
			APP_RECT CalculateBeforeScrollerRect();
			APP_RECT CalculateAfterScrollerRect();
			static void TimerCallback(void *param);
			int MouseToScroll(const int x, const int y);
			String StateToString(const STATE state);
			String ElementStateToString(const ELEMENT_STATE state);

			void PaintBackground(APP_RECT clip); // + border, + shadow
			void PaintElement(const ELEMENT_TYPE type, APP_RECT clip, APP_RECT rect);

			bool ProcessDownOnStartArrow(const int x, const int y);
			bool ProcessDownOnEndArrow(const int x, const int y);
			bool ProcessDownOnScroller(const int x, const int y);
			bool ProcessDownBeforeScroller(const int x, const int y);
			bool ProcessDownAfterScroller(const int x, const int y);
			bool ProcessMoveScroller(const int x, const int y);
			bool ProcessMoveOverStartArrow(const int x, const int y);
			bool ProcessMoveOverEndArrow(const int x, const int y);
			bool ProcessMoveOverScroller(const int x, const int y);
			bool ProcessMoveOverOther();
		protected:
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

			// Configurable properties
			TYPE m_eType;
			int m_iMin;
			int m_iMax;
			int m_iScroll;
			size_t m_iPageSize; // Change value by down not on scroller
			size_t m_iDeltaArrow; // Change value by arrows
			size_t m_iDeltaWheel; // Change value by wheel
			size_t m_iScrollerSize; // 0 for auto size
			size_t m_iBorderWidth;
			bool m_bBoxShadow;
			APP_POINT m_sBoxShadowShift;
			size_t m_iBoxShadowRadius;
			ELEMENT_SETTINGS m_aElements[etScroller + 1];
			BACKGROUND_STATE m_aBackground[stDisabled + 1];
			bool m_bVisible;
			bool m_bEnabled;
			APP_RECT m_sRect;

			virtual APP_RECT getRect();
			virtual bool getEnabled() const;
			virtual bool getVisible() const;
			virtual int getMin() const;
			virtual int getMax() const;
			virtual int getScroll() const;
			virtual size_t getPageSize() const;
			virtual size_t getDeltaArrow() const;
			virtual size_t getDeltaWheel() const;
			virtual TYPE getType() const;
			virtual STATE getState() const;
			virtual ELEMENT_STATE getElementState(const ELEMENT_TYPE type) const;
			virtual size_t getScrollerSize() const;
			virtual size_t getBorderWidth() const;
			virtual bool getBoxShadow() const;
			virtual APP_POINT getBoxShadowShift() const;
			virtual int getBoxShadowShiftX() const;
			virtual int getBoxShadowShiftY() const;
			virtual size_t getBoxShadowRadius() const;
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
			virtual bool getHovered() const;

			virtual bool setEnabled(const bool value);
			virtual bool setVisible(const bool value);
			virtual bool setMin(const int value);
			virtual bool setMax(const int value);
			virtual bool setScroll(int value);
			virtual bool setPageSize(size_t value);
			virtual bool setDeltaArrow(size_t value);
			virtual bool setDeltaWheel(size_t value);
			virtual bool setRect(const APP_RECT &rect);
			virtual bool setType(const TYPE value);
			virtual bool setScrollerSize(const size_t value);
			virtual bool setBorderWidth(const size_t value);
			virtual bool setBoxShadow(const bool value);
			virtual bool setBoxShadowShift(const APP_POINT &value);
			virtual bool setBoxShadowShiftX(const int value);
			virtual bool setBoxShadowShiftY(const int value);
			virtual bool setBoxShadowRadius(const size_t value);
			virtual bool setBackgroundColor(const STATE state, const APP_COLOR &value);
			virtual bool setBorderColor(const STATE state, const APP_COLOR &value);
			virtual bool setBoxShadowColor(const STATE state, const APP_COLOR &value);
			virtual bool setGradientType(const STATE state, const IImage::GRADIENT_TYPE value);
			virtual bool setGradientPointCount(const STATE state, const size_t value);
			virtual bool setGradientPointPosition(const STATE state, const size_t index, const double value);
			virtual bool setGradientPointColor(const STATE state, const size_t index, const APP_COLOR &value);
			virtual bool setGradientPoints(const STATE state, const size_t count, IImage::GRADIENT_POINT *points);
			virtual bool setElementBorderWidth(const ELEMENT_TYPE element, const size_t value);
			virtual bool setElementBorderRadius(const ELEMENT_TYPE element, const size_t value);
			virtual bool setElementBorderAntiAliazing(const ELEMENT_TYPE element, const size_t value);
			virtual bool setElementBackgroundColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const APP_COLOR &value);
			virtual bool setElementBorderColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const APP_COLOR &value);
			virtual bool setElementGradientType(const ELEMENT_TYPE element, const ELEMENT_STATE state, const IImage::GRADIENT_TYPE value);
			virtual bool setElementGradientPointCount(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t value);
			virtual bool setElementGradientPointPosition(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index, const double value);
			virtual bool setElementGradientPointColor(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t index, const APP_COLOR &value);
			virtual bool setElementGradientPoints(const ELEMENT_TYPE element, const ELEMENT_STATE state, const size_t count, IImage::GRADIENT_POINT *points);

			virtual bool UpdateFromStyle();
			virtual void Paint(APP_RECT clip);

			// Event handlers. Should be called when events occured on parent. Return true if event handled
			virtual bool ProcessMouseDown(const int x, const int y);
			virtual bool ProcessMouseUp();
			virtual bool ProcessMouseHover(const int x, const int y);
			virtual bool ProcessMouseLeave();
			virtual bool ProcessMouseMove(const int x, const int y, bool &repaint_required);
			virtual bool ProcessMouseWheel(const int x, const int y, const int delta);

			// Method to be implemented in derived class
			virtual String getClassName() const = 0;
			virtual CStyle *getStyle() = 0;
			virtual CForm *getForm() = 0;
			virtual APP_RECT ClientToForm(APP_RECT rect) = 0;
			virtual void NotifyOnChange() = 0;
		public:
			CBaseScrollBar();
		};
	}
}