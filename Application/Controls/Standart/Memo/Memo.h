// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Control.h"
#include "..\..\Base\BaseScrollBar.h"
#include "..\..\Base\BaseText.h"

namespace licui
{
	namespace application
	{
		class CMemo :public CControl
		{
		public:
			enum SCROLLBAR_VISIBILITY
			{
				sbvNone,
				sbvAuto,
				sbvVisible
			};
			enum STATE
			{
				stNormal,
				stHovered,
				stActive,
				stActiveHovered,
				stDisabled
			};
		private:
			class CMemoScrollBar :public CBaseScrollBar
			{
				friend CMemo;
			private:
				CMemo *m_pMemo;
			protected:
				String getClassName() const override;
				CStyle *getStyle() override;
				CForm *getForm() override;
				APP_RECT ClientToForm(APP_RECT rect) override;
				void NotifyOnChange() override;
			public:
				CMemoScrollBar(CMemo *memo, const TYPE type);
			public:
				
			};

			class CMemoText :public CBaseText
			{
				friend CMemo;
			private:
				CMemo *m_pMemo;
			protected:
				void NotifyOnChange() override;
				APP_RECT ClientToForm(APP_RECT rect) override;
				CForm *getForm() override;
				bool getEnabled() override;
				bool getFocused() override;
				IFont *getFont() override;
				CStyle *getStyle() override;
				String getClassName() override;
			public:
				CMemoText(CMemo *memo);
			public:
			};

			enum ELEMENT
			{
				elNone,
				elVScroll,
				elHScroll,
				elText,
				elControl // Border, padding
			};

			struct STYLE :IImage::GRADIENT
			{
				APP_COLOR BorderColor[4];
				APP_COLOR BackgroundColor;
				bool BoxShadow;
				APP_POINT BoxShadowShift;
				size_t BoxShadowRadius;
				APP_COLOR BoxShadowColor;
			};

			SCROLLBAR_VISIBILITY m_eVerticalScrollBarVisibility;
			SCROLLBAR_VISIBILITY m_eHorizontalScrollBarVisibility;
			ELEMENT m_eHoveredElement;
			ELEMENT m_eMouseDownElement; // When mouse was down
			size_t m_iScrollBarSize;
			CMemoScrollBar *m_pVerticalScrollBar;
			CMemoScrollBar *m_pHorizontalScrollBar;
			CMemoText *m_pText;
			math::RECTANGLE<size_t> m_sBorderWidth;
			math::RECTANGLE<size_t> m_sBorderRadius;
			size_t m_iBorderAntiAliazing;
			math::RECTANGLE<size_t> m_sPadding;
			STYLE m_aStyle[stDisabled + 1];
			math::RECTANGLE<size_t> m_sTextPadding;

			void FillStyles();
			void CalculateScrollBarsVisibility(bool &vscroll, bool &hscroll);
			void Update(); // If not enabled set scroll to 0
			bool UpdateHoveredElement(const int x, const int y); // Return true if hovered element was changed
			void UpdateAll(); // Call update, update scrollbars, update caret, repaint

			bool ProcessMouseDown(const int x, const int y, const bool ctrl, const bool alt, const bool shift);
			bool ProcessMouseUp(const int x, const int y, const bool ctrl, const bool shift);

			void PaintBackground(APP_RECT clip);
		protected:
			bool NotifyOnKeyDown(const IWindow::KEY key) override;
			bool NotifyOnChar(const wchar_t chr) override;
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

			void NotifyOnChangeUseParentFont() override;
			void NotifyOnParentFontChangeSize() override;
			void NotifyOnFontChangeSize() override;

			void NotifyOnMouseHover() override;
			void NotifyOnMouseLeave() override;
			void NotifyOnKillFocus() override;
			void NotifyOnSetFocus(CControl *old) override;
			void NotifyOnResetFocus() override;
			void NotifyOnKillCaptureMouse() override;
			void NotifyOnSetCaptureMouse() override;
			void NotifyOnChangeParentStyle() override;
			void NotifyOnChangeStyle() override;
			void NotifyOnPaint(APP_RECT clip) override;
			void NotifyOnResize(const APP_POINT &old_size, const APP_POINT &new_size) override;

			virtual void NotifyOnScrollBarChange(CMemoScrollBar *scrollbar);
			virtual void NotifyOnTextChange();

			bool UpdateFromStyle() override;
		public:
			APP_RECT getClientRect() override;
			APP_RECT getRenderRect() override;
			CURSOR_TYPE getCursor() const override;

			// Own getters & setters
			virtual STATE getState() const;
			virtual SCROLLBAR_VISIBILITY getVerticalScrollBarVisibility() const;
			virtual SCROLLBAR_VISIBILITY getHorizontalScrollBarVisibility() const;
			virtual size_t getScrollBarSize() const;
			virtual math::RECTANGLE<size_t> getBorderWidth() const;
			virtual size_t getBorderWidthLeft() const;
			virtual size_t getBorderWidthTop() const;
			virtual size_t getBorderWidthRight() const;
			virtual size_t getBorderWidthBottom() const;
			virtual math::RECTANGLE<size_t> getBorderRadius() const;
			virtual size_t getBorderRadiusLeftTop() const;
			virtual size_t getBorderRadiusRightTop() const;
			virtual size_t getBorderRadiusRightBottom() const;
			virtual size_t getBorderRadiusLeftBottom() const;
			virtual size_t getBorderAntiAliazing() const;
			virtual math::RECTANGLE<size_t> getPadding() const;
			virtual size_t getPaddingLeft() const;
			virtual size_t getPaddingTop() const;
			virtual size_t getPaddingRight() const;
			virtual size_t getPaddingBottom() const;
			virtual math::RECTANGLE<size_t> getTextPadding() const;
			virtual size_t getTextPaddingLeft() const;
			virtual size_t getTextPaddingTop() const;
			virtual size_t getTextPaddingRight() const;
			virtual size_t getTextPaddingBottom() const;
			virtual APP_COLOR getBorderColorLeft(const STATE state) const;
			virtual APP_COLOR getBorderColorTop(const STATE state) const;
			virtual APP_COLOR getBorderColorRight(const STATE state) const;
			virtual APP_COLOR getBorderColorBottom(const STATE state) const;
			virtual APP_COLOR getBackgroundColor(const STATE state) const;
			virtual bool getBoxShadow(const STATE state) const;
			virtual APP_POINT getBoxShadowShift(const STATE state) const;
			virtual int getBoxShadowShiftX(const STATE state) const;
			virtual int getBoxShadowShiftY(const STATE state) const;
			virtual size_t getBoxShadowRadius(const STATE state) const;
			virtual APP_COLOR getBoxShadowColor(const STATE state) const;
			virtual IImage::GRADIENT_TYPE getGradientType(const STATE state) const;
			virtual size_t getGradientPointCount(const STATE state) const;
			virtual double getGradientPointPosition(const STATE state, const size_t index) const;
			virtual APP_COLOR getGradientPointColor(const STATE state, const size_t index) const;

			virtual CMemo *setVerticalScrollBarVisibility(const SCROLLBAR_VISIBILITY value);
			virtual CMemo *setHorizontalScrollBarVisibility(const SCROLLBAR_VISIBILITY value);
			virtual CMemo *setScrollBarSize(size_t value);
			virtual CMemo *setBorderWidth(const math::RECTANGLE<size_t> &value);
			virtual CMemo *setBorderWidthLeft(const size_t value);
			virtual CMemo *setBorderWidthTop(const size_t value);
			virtual CMemo *setBorderWidthRight(const size_t value);
			virtual CMemo *setBorderWidthBottom(const size_t value);
			virtual CMemo *setBorderRadius(const math::RECTANGLE<size_t> &value);
			virtual CMemo *setBorderRadiusLeftTop(const size_t value);
			virtual CMemo *setBorderRadiusRightTop(const size_t value);
			virtual CMemo *setBorderRadiusRightBottom(const size_t value);
			virtual CMemo *setBorderRadiusLeftBottom(const size_t value);
			virtual CMemo *setBorderAntiAliazing(const size_t value);
			virtual CMemo *setPadding(const math::RECTANGLE<size_t> &value);
			virtual CMemo *setPaddingLeft(const size_t value);
			virtual CMemo *setPaddingTop(const size_t value);
			virtual CMemo *setPaddingRight(const size_t value);
			virtual CMemo *setPaddingBottom(const size_t value);
			virtual CMemo *setTextPadding(const math::RECTANGLE<size_t> &value);
			virtual CMemo *setTextPaddingLeft(const size_t value);
			virtual CMemo *setTextPaddingTop(const size_t value);
			virtual CMemo *setTextPaddingRight(const size_t value);
			virtual CMemo *setTextPaddingBottom(const size_t value);
			virtual CMemo *setBorderColorLeft(const STATE state, const APP_COLOR &value);
			virtual CMemo *setBorderColorTop(const STATE state, const APP_COLOR &value);
			virtual CMemo *setBorderColorRight(const STATE state, const APP_COLOR &value);
			virtual CMemo *setBorderColorBottom(const STATE state, const APP_COLOR &value);
			virtual CMemo *setBackgroundColor(const STATE state, const APP_COLOR &value);
			virtual CMemo *setBoxShadow(const STATE state, const bool value);
			virtual CMemo *setBoxShadowShift(const STATE state, const APP_POINT &value);
			virtual CMemo *setBoxShadowShiftX(const STATE state, const int value);
			virtual CMemo *setBoxShadowShiftY(const STATE state, const int value);
			virtual CMemo *setBoxShadowRadius(const STATE state, const size_t value);
			virtual CMemo *setBoxShadowColor(const STATE state, const APP_COLOR &value);
			virtual CMemo *setGradientType(const STATE state, const IImage::GRADIENT_TYPE value);
			virtual CMemo *setGradientPointCount(const STATE state, const size_t value);
			virtual CMemo *setGradientPointPosition(const STATE state, const size_t index, const double value);
			virtual CMemo *setGradientPointColor(const STATE state, const size_t index, const APP_COLOR &value);
			virtual CMemo *setGradientPoints(const STATE state, const size_t count, IImage::GRADIENT_POINT *points);

			// Text wrapers
			virtual size_t getLineHeight();
			virtual math::POINT<size_t> getLineMargin() const; // Top and bottom
			virtual size_t getLineMarginTop() const;
			virtual size_t getLineMarginBottom() const;
			virtual const String &getText() const;
			virtual APP_COLOR getTextColor(const CBaseText::STATE state) const;
			virtual APP_COLOR getShadowColor(const CBaseText::STATE state) const;
			virtual APP_COLOR getSelectionBackgroundColor(const CBaseText::STATE state) const;
			virtual APP_COLOR getSelectionTextColor(const CBaseText::STATE state) const;
			virtual APP_COLOR getSelectionShadowColor(const CBaseText::STATE state) const;
			virtual size_t getMaxLength() const;
			virtual bool getReadOnly() const;
			virtual bool getInserting() const;
			virtual math::POINT<size_t> getSelection() const;
			virtual size_t getCaretPosition() const;
			virtual size_t getDeltaWheelVertical() const;
			virtual size_t getDeltaWheelHorizontal() const;
			virtual size_t getHistoryLimitCount() const;
			virtual size_t getHistoryLimitSize() const;

			virtual CMemo *setLineMargin(const math::POINT<size_t> &value);
			virtual CMemo *setLineMarginTop(const size_t value);
			virtual CMemo *setLineMarginBottom(const size_t value);
			virtual CMemo *setText(const String &value);
			virtual CMemo *setTextColor(const CBaseText::STATE state, const APP_COLOR &value);
			virtual CMemo *setShadowColor(const CBaseText::STATE state, const APP_COLOR &value);
			virtual CMemo *setSelectionBackgroundColor(const CBaseText::STATE state, const APP_COLOR &value);
			virtual CMemo *setSelectionTextColor(const CBaseText::STATE state, const APP_COLOR &value);
			virtual CMemo *setSelectionShadowColor(const CBaseText::STATE state, const APP_COLOR &value);
			virtual CMemo *setMaxLength(const size_t value);
			virtual CMemo *setReadOnly(const bool value);
			virtual CMemo *setInserting(const bool value);
			virtual CMemo *setSelection(const math::POINT<size_t> &value);
			virtual CMemo *setCaretPosition(const size_t value);
			virtual CMemo *setDeltaWheelVertical(const size_t value);
			virtual CMemo *setDeltaWheelHorizontal(const size_t value);
			virtual CMemo *setHistoryLimitCount(const size_t value);
			virtual CMemo *setHistoryLimitSize(const size_t value);

			virtual CMemo *ScrollToCaret();
			virtual bool CanUndo();
			virtual bool CanRedo();
			virtual CMemo *Undo();
			virtual CMemo *Redo();
			virtual CMemo *ScrollLineUp();
			virtual CMemo *MoveCaretLineUpAndSelect();
			virtual CMemo *MoveCaretLineUp();
			virtual CMemo *ScrollLineDown();
			virtual CMemo *MoveCaretLineDownAndSelect();
			virtual CMemo *MoveCaretLineDown();
			virtual CMemo *MoveCaretWordStartAndSelect();
			virtual CMemo *MoveCaretWordStart();
			virtual CMemo *MoveCaretLeftAndSelect();
			virtual CMemo *MoveCaretLeft();
			virtual CMemo *MoveCaretWordEndAndSelect();
			virtual CMemo *MoveCaretWordEnd();
			virtual CMemo *MoveCaretRightAndSelect();
			virtual CMemo *MoveCaretRight();
			virtual CMemo *DeleteSelection();
			virtual CMemo *DeleteLeft();
			virtual CMemo *DeleteRight();
			virtual CMemo *MoveCaretTextStartAndSelect();
			virtual CMemo *MoveCaretTextStart();
			virtual CMemo *MoveCaretLineStartAndSelect();
			virtual CMemo *MoveCaretLineStart();
			virtual CMemo *MoveCaretTextEndAndSelect();
			virtual CMemo *MoveCaretTextEnd();
			virtual CMemo *MoveCaretLineEndAndSelect();
			virtual CMemo *MoveCaretLineEnd();
			virtual CMemo *MoveCaretPageStartAndSelect();
			virtual CMemo *MoveCaretPageStart();
			virtual CMemo *MoveCaretPageUpAndSelect();
			virtual CMemo *MoveCaretPageUp();
			virtual CMemo *MoveCaretPageEndAndSelect();
			virtual CMemo *MoveCaretPageEnd();
			virtual CMemo *MoveCaretPageDownAndSelect();
			virtual CMemo *MoveCaretPageDown();
			virtual CMemo *SelectAll();
			virtual CMemo *Paste();
			virtual CMemo *Copy();
			virtual CMemo *Cut();
			virtual CMemo *ClearHistory();

			// VerticalScrollBar wrapers
			virtual bool getVerticalScrollBarEnabled() const;
			virtual bool getVerticalScrollBarVisible() const;
			virtual int getVerticalScrollBarMax() const;
			virtual int getVerticalScrollBarScroll() const;
			virtual size_t getVerticalScrollBarPageSize() const;
			virtual size_t getVerticalScrollBarDeltaArrow() const;
			virtual size_t getVerticalScrollBarDeltaWheel() const;
			virtual CBaseScrollBar::ELEMENT_STATE getVerticalScrollBarElementState(const CBaseScrollBar::ELEMENT_TYPE type) const;
			virtual size_t getVerticalScrollBarScrollerSize() const;
			virtual size_t getVerticalScrollBarBorderWidth() const;
			virtual bool getVerticalScrollBarBoxShadow() const;
			virtual APP_POINT getVerticalScrollBarBoxShadowShift() const;
			virtual int getVerticalScrollBarBoxShadowShiftX() const;
			virtual int getVerticalScrollBarBoxShadowShiftY() const;
			virtual size_t getVerticalScrollBarBoxShadowRadius() const;
			virtual APP_COLOR getVerticalScrollBarBackgroundColor(const CBaseScrollBar::STATE state) const;
			virtual APP_COLOR getVerticalScrollBarBorderColor(const CBaseScrollBar::STATE state) const;
			virtual APP_COLOR getVerticalScrollBarBoxShadowColor(const CBaseScrollBar::STATE state) const;
			virtual IImage::GRADIENT_TYPE getVerticalScrollBarGradientType(const CBaseScrollBar::STATE state) const;
			virtual size_t getVerticalScrollBarGradientPointCount(const CBaseScrollBar::STATE state) const;
			virtual double getVerticalScrollBarGradientPointPosition(const CBaseScrollBar::STATE state, const size_t index) const;
			virtual APP_COLOR getVerticalScrollBarGradientPointColor(const CBaseScrollBar::STATE state, const size_t index) const;
			virtual size_t getVerticalScrollBarElementBorderWidth(const CBaseScrollBar::ELEMENT_TYPE element) const;
			virtual size_t getVerticalScrollBarElementBorderRadius(const CBaseScrollBar::ELEMENT_TYPE element) const;
			virtual size_t getVerticalScrollBarElementBorderAntiAliazing(const CBaseScrollBar::ELEMENT_TYPE element) const;
			virtual APP_COLOR getVerticalScrollBarElementBackgroundColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const;
			virtual APP_COLOR getVerticalScrollBarElementBorderColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const;
			virtual IImage::GRADIENT_TYPE getVerticalScrollBarElementGradientType(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const;
			virtual size_t getVerticalScrollBarElementGradientPointCount(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const;
			virtual double getVerticalScrollBarElementGradientPointPosition(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index) const;
			virtual APP_COLOR getVerticalScrollBarElementGradientPointColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index) const;
			virtual bool getVerticalScrollBarHovered() const;

			virtual CMemo *setVerticalScrollBarScroll(const int value);
			virtual CMemo *setVerticalScrollBarDeltaArrow(const size_t value);
			virtual CMemo *setVerticalScrollBarDeltaWheel(const size_t value);
			virtual CMemo *setVerticalScrollBarBorderWidth(const size_t value);
			virtual CMemo *setVerticalScrollBarBoxShadow(const bool value);
			virtual CMemo *setVerticalScrollBarBoxShadowShift(const APP_POINT &value);
			virtual CMemo *setVerticalScrollBarBoxShadowShiftX(const int value);
			virtual CMemo *setVerticalScrollBarBoxShadowShiftY(const int value);
			virtual CMemo *setVerticalScrollBarBoxShadowRadius(const size_t value);
			virtual CMemo *setVerticalScrollBarBackgroundColor(const CBaseScrollBar::STATE state, const APP_COLOR &value);
			virtual CMemo *setVerticalScrollBarBorderColor(const CBaseScrollBar::STATE state, const APP_COLOR &value);
			virtual CMemo *setVerticalScrollBarBoxShadowColor(const CBaseScrollBar::STATE state, const APP_COLOR &value);
			virtual CMemo *setVerticalScrollBarGradientType(const CBaseScrollBar::STATE state, const IImage::GRADIENT_TYPE value);
			virtual CMemo *setVerticalScrollBarGradientPointCount(const CBaseScrollBar::STATE state, const size_t value);
			virtual CMemo *setVerticalScrollBarGradientPointPosition(const CBaseScrollBar::STATE state, const size_t index, const double value);
			virtual CMemo *setVerticalScrollBarGradientPointColor(const CBaseScrollBar::STATE state, const size_t index, const APP_COLOR &value);
			virtual CMemo *setVerticalScrollBarGradientPoints(const CBaseScrollBar::STATE state, const size_t count, IImage::GRADIENT_POINT *points);
			virtual CMemo *setVerticalScrollBarElementBorderWidth(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value);
			virtual CMemo *setVerticalScrollBarElementBorderRadius(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value);
			virtual CMemo *setVerticalScrollBarElementBorderAntiAliazing(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value);
			virtual CMemo *setVerticalScrollBarElementBackgroundColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const APP_COLOR &value);
			virtual CMemo *setVerticalScrollBarElementBorderColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const APP_COLOR &value);
			virtual CMemo *setVerticalScrollBarElementGradientType(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const IImage::GRADIENT_TYPE value);
			virtual CMemo *setVerticalScrollBarElementGradientPointCount(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t value);
			virtual CMemo *setVerticalScrollBarElementGradientPointPosition(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index, const double value);
			virtual CMemo *setVerticalScrollBarElementGradientPointColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index, const APP_COLOR &value);
			virtual CMemo *setVerticalScrollBarElementGradientPoints(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t count, IImage::GRADIENT_POINT *points);

			// HorizontalScrollBar wrapers
			virtual bool getHorizontalScrollBarEnabled() const;
			virtual bool getHorizontalScrollBarVisible() const;
			virtual int getHorizontalScrollBarMax() const;
			virtual int getHorizontalScrollBarScroll() const;
			virtual size_t getHorizontalScrollBarPageSize() const;
			virtual size_t getHorizontalScrollBarDeltaArrow() const;
			virtual size_t getHorizontalScrollBarDeltaWheel() const;
			virtual CBaseScrollBar::ELEMENT_STATE getHorizontalScrollBarElementState(const CBaseScrollBar::ELEMENT_TYPE type) const;
			virtual size_t getHorizontalScrollBarScrollerSize() const;
			virtual size_t getHorizontalScrollBarBorderWidth() const;
			virtual bool getHorizontalScrollBarBoxShadow() const;
			virtual APP_POINT getHorizontalScrollBarBoxShadowShift() const;
			virtual int getHorizontalScrollBarBoxShadowShiftX() const;
			virtual int getHorizontalScrollBarBoxShadowShiftY() const;
			virtual size_t getHorizontalScrollBarBoxShadowRadius() const;
			virtual APP_COLOR getHorizontalScrollBarBackgroundColor(const CBaseScrollBar::STATE state) const;
			virtual APP_COLOR getHorizontalScrollBarBorderColor(const CBaseScrollBar::STATE state) const;
			virtual APP_COLOR getHorizontalScrollBarBoxShadowColor(const CBaseScrollBar::STATE state) const;
			virtual IImage::GRADIENT_TYPE getHorizontalScrollBarGradientType(const CBaseScrollBar::STATE state) const;
			virtual size_t getHorizontalScrollBarGradientPointCount(const CBaseScrollBar::STATE state) const;
			virtual double getHorizontalScrollBarGradientPointPosition(const CBaseScrollBar::STATE state, const size_t index) const;
			virtual APP_COLOR getHorizontalScrollBarGradientPointColor(const CBaseScrollBar::STATE state, const size_t index) const;
			virtual size_t getHorizontalScrollBarElementBorderWidth(const CBaseScrollBar::ELEMENT_TYPE element) const;
			virtual size_t getHorizontalScrollBarElementBorderRadius(const CBaseScrollBar::ELEMENT_TYPE element) const;
			virtual size_t getHorizontalScrollBarElementBorderAntiAliazing(const CBaseScrollBar::ELEMENT_TYPE element) const;
			virtual APP_COLOR getHorizontalScrollBarElementBackgroundColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const;
			virtual APP_COLOR getHorizontalScrollBarElementBorderColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const;
			virtual IImage::GRADIENT_TYPE getHorizontalScrollBarElementGradientType(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const;
			virtual size_t getHorizontalScrollBarElementGradientPointCount(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state) const;
			virtual double getHorizontalScrollBarElementGradientPointPosition(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index) const;
			virtual APP_COLOR getHorizontalScrollBarElementGradientPointColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index) const;
			virtual bool getHorizontalScrollBarHovered() const;

			virtual CMemo *setHorizontalScrollBarScroll(const int value);
			virtual CMemo *setHorizontalScrollBarDeltaArrow(const size_t value);
			virtual CMemo *setHorizontalScrollBarDeltaWheel(const size_t value);
			virtual CMemo *setHorizontalScrollBarBorderWidth(const size_t value);
			virtual CMemo *setHorizontalScrollBarBoxShadow(const bool value);
			virtual CMemo *setHorizontalScrollBarBoxShadowShift(const APP_POINT &value);
			virtual CMemo *setHorizontalScrollBarBoxShadowShiftX(const int value);
			virtual CMemo *setHorizontalScrollBarBoxShadowShiftY(const int value);
			virtual CMemo *setHorizontalScrollBarBoxShadowRadius(const size_t value);
			virtual CMemo *setHorizontalScrollBarBackgroundColor(const CBaseScrollBar::STATE state, const APP_COLOR &value);
			virtual CMemo *setHorizontalScrollBarBorderColor(const CBaseScrollBar::STATE state, const APP_COLOR &value);
			virtual CMemo *setHorizontalScrollBarBoxShadowColor(const CBaseScrollBar::STATE state, const APP_COLOR &value);
			virtual CMemo *setHorizontalScrollBarGradientType(const CBaseScrollBar::STATE state, const IImage::GRADIENT_TYPE value);
			virtual CMemo *setHorizontalScrollBarGradientPointCount(const CBaseScrollBar::STATE state, const size_t value);
			virtual CMemo *setHorizontalScrollBarGradientPointPosition(const CBaseScrollBar::STATE state, const size_t index, const double value);
			virtual CMemo *setHorizontalScrollBarGradientPointColor(const CBaseScrollBar::STATE state, const size_t index, const APP_COLOR &value);
			virtual CMemo *setHorizontalScrollBarGradientPoints(const CBaseScrollBar::STATE state, const size_t count, IImage::GRADIENT_POINT *points);
			virtual CMemo *setHorizontalScrollBarElementBorderWidth(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value);
			virtual CMemo *setHorizontalScrollBarElementBorderRadius(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value);
			virtual CMemo *setHorizontalScrollBarElementBorderAntiAliazing(const CBaseScrollBar::ELEMENT_TYPE element, const size_t value);
			virtual CMemo *setHorizontalScrollBarElementBackgroundColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const APP_COLOR &value);
			virtual CMemo *setHorizontalScrollBarElementBorderColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const APP_COLOR &value);
			virtual CMemo *setHorizontalScrollBarElementGradientType(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const IImage::GRADIENT_TYPE value);
			virtual CMemo *setHorizontalScrollBarElementGradientPointCount(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t value);
			virtual CMemo *setHorizontalScrollBarElementGradientPointPosition(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index, const double value);
			virtual CMemo *setHorizontalScrollBarElementGradientPointColor(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t index, const APP_COLOR &value);
			virtual CMemo *setHorizontalScrollBarElementGradientPoints(const CBaseScrollBar::ELEMENT_TYPE element, const CBaseScrollBar::ELEMENT_STATE state, const size_t count, IImage::GRADIENT_POINT *points);

			CMemo();
			CMemo(CForm *form);
			CMemo(CControl *parent);
			~CMemo();
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
			using CControl::setAlign;
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