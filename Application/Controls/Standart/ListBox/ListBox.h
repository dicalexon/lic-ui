// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Control.h"
#include "..\ScrollBar\ScrollBar.h"
#include <chrono>

namespace licui
{
	namespace application
	{
		class CCustomListBoxItem;
		class CCustomListBox;
		class CListBoxItem;
		class CListBox;

		class CCustomListBoxItem
		{
			friend CCustomListBox;
		protected:
			virtual math::POINT<size_t> CalculateSize() = 0;
			virtual void Paint(APP_RECT clip, APP_RECT rect) = 0;
			virtual void UpdateFromStyle() = 0;

			virtual void NotifyOnClick() = 0;
			virtual void NotifyOnSelect() = 0;
			virtual void NotifyOnDeselect() = 0;
			virtual void NotifyOnActivate() = 0;
			virtual void NotifyOnDeactivate() = 0;
			virtual void NotifyOnHover() = 0;
			virtual void NotifyOnLeave() = 0;

			virtual bool getSelectedInternal() const = 0;
			virtual bool setSelectedInternal(const bool value) = 0;  // Return if changed
		public:
		};

		class CCustomListBox :public CControl
		{
		public:
			enum STATE
			{
				stNormal,
				stHovered,
				stActive,
				stDisabled
			};
			enum SCROLLBAR
			{
				sbNone,
				sbAuto,
				sbVisible
			};
		private:
			class CListBoxScrollBar :public CScrollBar
			{
			protected:
				void NotifyOnScroll() override;
				void NotifyOnMouseHover() override;
				void NotifyOnMouseLeave() override;
			public:
				CListBoxScrollBar(CCustomListBox *parent);
			};

			std::vector<CCustomListBoxItem*> m_aItems;
			std::chrono::steady_clock::time_point m_iLastPressedCharTime;
			unsigned int m_hTimer;

			static void TimerCallback(void *param);
		protected:
			bool UpdateFromStyle() override;

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
			void NotifyOnShow() override;
			void NotifyOnPaint(APP_RECT clip) override;
			void NotifyOnResize(const APP_POINT &old_size, const APP_POINT &new_size) override;

			virtual void NotifyOnScroll(CListBoxScrollBar *sender);

			size_t m_iColumns;
			size_t m_iBorderWidth;
			APP_COLOR m_aBorderColor[stDisabled + 1];
			APP_COLOR m_aBackgroundColor[stDisabled + 1];
			bool m_bBoxShadow;
			APP_POINT m_sBoxShadowShift;
			size_t m_iBoxShadowRadius;
			APP_COLOR m_aBoxShadowColor[stDisabled + 1];
			math::RECTANGLE<size_t> m_sPadding;
			SCROLLBAR m_eVerticalScrollBar;
			SCROLLBAR m_eHorizontalScrollBar;
			int m_iActiveItemIndex;
			size_t m_iResetSearchInterval; // Milliseconds
			String m_sSearchChars;
			bool m_bAllowMultiSelect;
			bool m_bAllowSearch;

			math::POINT<size_t> m_sItemSize;
			bool m_bMouseDown;
			bool m_bMouseDownWithCtrl;
			bool m_bMouseDownWithShift;
			int m_iHoverItemIndex;

			virtual CListBoxScrollBar *getVScrollBar();
			virtual CListBoxScrollBar *getHScrollBar();
			virtual bool PosToGrid(const int x, const int y, int &col, int &row); // Convert form coordinates to virtual grid coordinates. Return false if no items exists, or items size is unknown
			virtual int ItemAtPos(const int x, const int y);
			virtual bool ItemIndexToGrid(const int index, int &col, int &row);
			virtual bool GridSize(int &cols, int &rows);
			virtual bool DeselectAllInternal();
			virtual void DeselectAllExceptFirst();
			virtual void Update();
			virtual void ScrollToItem(const int index);
			virtual void StartCapture();
			virtual void EndCapture();

			virtual void ProcessKeyUp(const bool shift);
			virtual void ProcessKeyDown(const bool shift);
			virtual void ProcessKeyLeft(const bool shift);
			virtual void ProcessKeyRight(const bool shift);
			virtual void ProcessKeyHome(const bool shift);
			virtual void ProcessKeyEnd(const bool shift);
			virtual void ProcessKeyPageUp(const bool shift);
			virtual void ProcessKeyPageDown(const bool shift);
			virtual void ProcessKeySpace();
			virtual void ProcessKeyReturn();
			virtual void ProcessSearch(); // Got to item starting by m_sSearchChars
			virtual void ProcessMouseMove(const int x, const int y); // When mouse was down
			virtual void ProcessTimer();

			virtual void PaintBoxShadow(APP_RECT clip);
			virtual void PaintBackground(APP_RECT clip);
			virtual void PaintItems(APP_RECT clip);
			virtual void PaintScrollbarsCorner(APP_RECT clip);

			virtual STATE getState();
			virtual size_t getColumns() const;
			virtual size_t getBorderWidth() const;
			virtual APP_COLOR getBorderColor(const STATE state) const;
			virtual APP_COLOR getBackgroundColor(const STATE state) const;
			virtual bool getBoxShadow() const;
			virtual APP_POINT getBoxShadowShift() const;
			virtual int getBoxShadowShiftX() const;
			virtual int getBoxShadowShiftY() const;
			virtual size_t getBoxShadowRadius() const;
			virtual APP_COLOR getBoxShadowColor(const STATE state) const;
			virtual math::RECTANGLE<size_t> getPadding() const;
			virtual size_t getPaddingLeft() const;
			virtual size_t getPaddingTop() const;
			virtual size_t getPaddingRight() const;
			virtual size_t getPaddingBottom() const;
			virtual SCROLLBAR getVerticalScrollBar() const;
			virtual SCROLLBAR getHorizontalScrollBar() const;
			virtual size_t getItemCount() const;
			virtual CCustomListBoxItem *getItem(const size_t index);
			virtual int getActiveItemIndex() const;
			virtual CCustomListBoxItem *getActiveItem();
			virtual CCustomListBoxItem *getHoveredItem();
			virtual size_t getResetSearchInterval() const;
			virtual bool getAllowMultiSelect() const;
			virtual bool getAllowSearch() const;

			virtual CCustomListBox *setColumns(size_t value);
			virtual CCustomListBox *setBorderWidth(const size_t value);
			virtual CCustomListBox *setBorderColor(const STATE state, const APP_COLOR &value);
			virtual CCustomListBox *setBackgroundColor(const STATE state, const APP_COLOR &value);
			virtual CCustomListBox *setBoxShadow(const bool value);
			virtual CCustomListBox *setBoxShadowShift(const APP_POINT &value);
			virtual CCustomListBox *setBoxShadowShiftX(const int value);
			virtual CCustomListBox *setBoxShadowShiftY(const int value);
			virtual CCustomListBox *setBoxShadowRadius(const size_t value);
			virtual CCustomListBox *setBoxShadowColor(const STATE state, const APP_COLOR &value);
			virtual CCustomListBox *setPadding(const math::RECTANGLE<size_t> &value);
			virtual CCustomListBox *setPaddingLeft(const size_t value);
			virtual CCustomListBox *setPaddingTop(const size_t value);
			virtual CCustomListBox *setPaddingRight(const size_t value);
			virtual CCustomListBox *setPaddingBottom(const size_t value);
			virtual CCustomListBox *setVerticalScrollBar(const SCROLLBAR value);
			virtual CCustomListBox *setHorizontalScrollBar(const SCROLLBAR value);
			virtual CCustomListBox *setActiveItemIndex(int value);
			virtual CCustomListBox *setResetSearchInterval(const size_t value);
			virtual CCustomListBox *setAllowMultiSelect(const bool value);
			virtual CCustomListBox *setAllowSearch(const bool value);

			virtual CCustomListBox *Add(CCustomListBoxItem *item);
			virtual CCustomListBox *Insert(const size_t before, CCustomListBoxItem *item);
			virtual CCustomListBox *Delete(const size_t index);
			virtual CCustomListBox *DeleteAll();
			virtual CCustomListBox *DeleteSelected();
			virtual CCustomListBox *DeleteUnselected();
			virtual CCustomListBox *SelectAll();
			virtual CCustomListBox *DeselectAll();
			virtual CCustomListBox *InvertSelection();
			virtual CCustomListBox *SelectRange(size_t start, size_t end);
		public:
			APP_RECT getClientRect() override;
			APP_RECT getRenderRect() override;

			CCustomListBox();
			~CCustomListBox() override; // Call DeleteAll() in derived class if items uses notifications and access parent inside it
		};

		class CListBoxItem :public CCustomListBoxItem
		{
			friend CListBox;
		public:
			enum STATE
			{
				stNormal,
				stNormalHovered,
				stActive,
				stActiveHovered,
				stActiveSelected,
				stActiveSelectedHovered,
				stSelected,
				stSelectedHovered,
				stDisabled
			};
		private:
			CListBox *m_pListBox;
			String m_sCaption;
			bool m_bSelected;
			math::RECTANGLE<size_t> m_sPadding;
			size_t m_iBorderWidth;
			APP_COLOR m_aBorderColor[stDisabled + 1];
			APP_COLOR m_aBackgroundColor[stDisabled + 1];
			APP_COLOR m_aTextColor[stDisabled + 1];
			APP_COLOR m_aShadowColor[stDisabled + 1];
		protected:
			math::POINT<size_t> CalculateSize() override;
			void Paint(APP_RECT clip, APP_RECT rect) override;
			void UpdateFromStyle() override;

			void NotifyOnClick() override;
			void NotifyOnSelect() override;
			void NotifyOnDeselect() override;
			void NotifyOnActivate() override;
			void NotifyOnDeactivate() override;
			void NotifyOnHover() override;
			void NotifyOnLeave() override;

			bool getSelectedInternal() const override;
			bool setSelectedInternal(const bool value) override;
		public:
			virtual STATE getState() const;
			virtual String getCaption() const;
			virtual bool getSelected() const;
			virtual math::RECTANGLE<size_t> getPadding() const;
			virtual size_t getPaddingLeft() const;
			virtual size_t getPaddingTop() const;
			virtual size_t getPaddingRight() const;
			virtual size_t getPaddingBottom() const;
			virtual size_t getBorderWidth() const;
			virtual APP_COLOR getBorderColor(const STATE state) const;
			virtual APP_COLOR getBackgroundColor(const STATE state) const;
			virtual APP_COLOR getTextColor(const STATE state) const;
			virtual APP_COLOR getShadowColor(const STATE state) const;

			virtual CListBoxItem *setCaption(const String &value);
			virtual CListBoxItem *setSelected(const bool value);
			virtual CListBoxItem *setPadding(const math::RECTANGLE<size_t> &value);
			virtual CListBoxItem *setPaddingLeft(const size_t value);
			virtual CListBoxItem *setPaddingTop(const size_t value);
			virtual CListBoxItem *setPaddingRight(const size_t value);
			virtual CListBoxItem *setPaddingBottom(const size_t value);
			virtual CListBoxItem *setBorderWidth(const size_t value);
			virtual CListBoxItem *setBorderColor(const STATE state, const APP_COLOR &value);
			virtual CListBoxItem *setBackgroundColor(const STATE state, const APP_COLOR &value);
			virtual CListBoxItem *setTextColor(const STATE state, const APP_COLOR &value);
			virtual CListBoxItem *setShadowColor(const STATE state, const APP_COLOR &value);

			CListBoxItem();
		};

		class CListBox :public CCustomListBox
		{
			friend CListBoxItem;
		public:
			typedef void(*FOnClickItem)(CListBoxItem *item, void *param);
			typedef void(*FOnSelectItem)(CListBoxItem *item, void *param);
			typedef void(*FOnDeselectItem)(CListBoxItem *item, void *param);
			typedef void(*FOnActivateItem)(CListBoxItem *item, void *param);
			typedef void(*FOnDeactivateItem)(CListBoxItem *item, void *param);
			typedef void(*FOnHoverItem)(CListBoxItem *item, void *param);
			typedef void(*FOnLeaveItem)(CListBoxItem *item, void *param);
		private:
			FOnClickItem m_fOnClickItem;
			FOnSelectItem m_fOnSelectItem;
			FOnDeselectItem m_fOnDeselectItem;
			FOnActivateItem m_fOnActivateItem;
			FOnDeactivateItem m_fOnDeactivateItem;
			FOnHoverItem m_fOnHoverItem;
			FOnLeaveItem m_fOnLeaveItem;
		protected:
			void ProcessSearch() override;

			virtual void NotifyOnClickItem(CListBoxItem *item);
			virtual void NotifyOnSelectItem(CListBoxItem *item);
			virtual void NotifyOnDeselectItem(CListBoxItem *item);
			virtual void NotifyOnActivateItem(CListBoxItem *item);
			virtual void NotifyOnDeactivateItem(CListBoxItem *item);
			virtual void NotifyOnHoverItem(CListBoxItem *item);
			virtual void NotifyOnLeaveItem(CListBoxItem *item);
		public:
			virtual CListBoxItem *getItem(const size_t index);
			virtual CListBoxItem *getActiveItem();
			virtual CListBoxItem *getHoveredItem();

			virtual FOnClickItem getOnClickItem() const;
			virtual FOnSelectItem getOnSelectItem() const;
			virtual FOnDeselectItem getOnDeselectItem() const;
			virtual FOnActivateItem getOnActivateItem() const;
			virtual FOnDeactivateItem getOnDeactivateItem() const;
			virtual FOnHoverItem getOnHoverItem() const;
			virtual FOnLeaveItem getOnLeaveItem() const;

			virtual CListBox *setOnClickItem(FOnClickItem value);
			virtual CListBox *setOnSelectItem(FOnSelectItem value);
			virtual CListBox *setOnDeselectItem(FOnDeselectItem value);
			virtual CListBox *setOnActivateItem(FOnActivateItem value);
			virtual CListBox *setOnDeactivateItem(FOnDeactivateItem value);
			virtual CListBox *setOnHoverItem(FOnHoverItem value);
			virtual CListBox *setOnLeaveItem(FOnLeaveItem value);

			CListBox();
			CListBox(CForm *form);
			CListBox(CControl *parent);
			~CListBox() override;

			virtual CListBox *Add(CListBoxItem *item);
			virtual CListBox *Insert(const size_t before, CListBoxItem *item);
		public:
			using CCustomListBox::getOnKeyDown;
			using CCustomListBox::getOnKeyUp;
			using CCustomListBox::getOnChar;
			using CCustomListBox::getOnDeadChar;
			using CCustomListBox::getOnSysKeyDown;
			using CCustomListBox::getOnSysKeyUp;
			using CCustomListBox::getOnSysChar;
			using CCustomListBox::getOnSysDeadChar;
			using CCustomListBox::getOnMouseMove;
			using CCustomListBox::getOnLeftMouseButtonDown;
			using CCustomListBox::getOnLeftMouseButtonUp;
			using CCustomListBox::getOnLeftMouseButtonDoubleClick;
			using CCustomListBox::getOnRightMouseButtonDown;
			using CCustomListBox::getOnRightMouseButtonUp;
			using CCustomListBox::getOnRightMouseButtonDoubleClick;
			using CCustomListBox::getOnMiddleMouseButtonDown;
			using CCustomListBox::getOnMiddleMouseButtonUp;
			using CCustomListBox::getOnMiddleMouseButtonDoubleClick;
			using CCustomListBox::getOnMouseVerticalWheel;
			using CCustomListBox::getOnMouseHorizontalWheel;
			using CCustomListBox::getOnChangeUseParentFont;
			using CCustomListBox::getOnParentFontChangeName;
			using CCustomListBox::getOnParentFontChangeHeight;
			using CCustomListBox::getOnParentFontChangeWeight;
			using CCustomListBox::getOnParentFontChangeItalic;
			using CCustomListBox::getOnParentFontChangeUnderline;
			using CCustomListBox::getOnParentFontChangeStrikeOut;
			using CCustomListBox::getOnParentFontChangeWidth;
			using CCustomListBox::getOnParentFontChangeCharSet;
			using CCustomListBox::getOnParentFontChangeQuality;
			using CCustomListBox::getOnParentFontChangePitchAndFamily;
			using CCustomListBox::getOnParentFontChangeOrientation;
			using CCustomListBox::getOnParentFontChangeDistance;
			using CCustomListBox::getOnParentFontChangeShadow;
			using CCustomListBox::getOnParentFontChangeShadowShift;
			using CCustomListBox::getOnParentFontChangeShadowBlur;
			using CCustomListBox::getOnParentFontChangeShadowColor;
			using CCustomListBox::getOnParentFontChangeColor;
			using CCustomListBox::getOnParentFontChangeInterpolate;
			using CCustomListBox::getOnParentFontBeginChange;
			using CCustomListBox::getOnParentFontEndChange;
			using CCustomListBox::getOnParentFontChangeSize;
			using CCustomListBox::getOnParentFontChangeStyle;
			using CCustomListBox::getOnFontChangeName;
			using CCustomListBox::getOnFontChangeHeight;
			using CCustomListBox::getOnFontChangeWeight;
			using CCustomListBox::getOnFontChangeItalic;
			using CCustomListBox::getOnFontChangeUnderline;
			using CCustomListBox::getOnFontChangeStrikeOut;
			using CCustomListBox::getOnFontChangeWidth;
			using CCustomListBox::getOnFontChangeCharSet;
			using CCustomListBox::getOnFontChangeQuality;
			using CCustomListBox::getOnFontChangePitchAndFamily;
			using CCustomListBox::getOnFontChangeOrientation;
			using CCustomListBox::getOnFontChangeDistance;
			using CCustomListBox::getOnFontChangeShadow;
			using CCustomListBox::getOnFontChangeShadowShift;
			using CCustomListBox::getOnFontChangeShadowBlur;
			using CCustomListBox::getOnFontChangeShadowColor;
			using CCustomListBox::getOnFontChangeColor;
			using CCustomListBox::getOnFontChangeInterpolate;
			using CCustomListBox::getOnFontBeginChange;
			using CCustomListBox::getOnFontEndChange;
			using CCustomListBox::getOnFontChangeSize;
			using CCustomListBox::getOnFontChangeStyle;
			using CCustomListBox::getOnMouseHover;
			using CCustomListBox::getOnMouseLeave;
			using CCustomListBox::getOnKillFocus;
			using CCustomListBox::getOnSetFocus;
			using CCustomListBox::getOnResetFocus;
			using CCustomListBox::getOnKillCaptureMouse;
			using CCustomListBox::getOnSetCaptureMouse;
			using CCustomListBox::getOnChangeParentStyle;
			using CCustomListBox::getOnChangeStyle;
			using CCustomListBox::getOnShow;
			using CCustomListBox::getOnBeforeHide;
			using CCustomListBox::getOnHide;
			using CCustomListBox::getOnEnable;
			using CCustomListBox::getOnDisable;
			using CCustomListBox::getOnPaint;
			using CCustomListBox::getOnParentResize;
			using CCustomListBox::getOnParentMove;
			using CCustomListBox::getOnBeforeResize;
			using CCustomListBox::getOnResize;
			using CCustomListBox::getOnBeforeMove;
			using CCustomListBox::getOnMove;
			using CCustomListBox::getOnBeforeDetachFromControl;
			using CCustomListBox::getOnDetachFromControl;
			using CCustomListBox::getOnAttachToControl;
			using CCustomListBox::setOnKeyDown;
			using CCustomListBox::setOnKeyUp;
			using CCustomListBox::setOnChar;
			using CCustomListBox::setOnDeadChar;
			using CCustomListBox::setOnSysKeyDown;
			using CCustomListBox::setOnSysKeyUp;
			using CCustomListBox::setOnSysChar;
			using CCustomListBox::setOnSysDeadChar;
			using CCustomListBox::setOnMouseMove;
			using CCustomListBox::setOnLeftMouseButtonDown;
			using CCustomListBox::setOnLeftMouseButtonUp;
			using CCustomListBox::setOnLeftMouseButtonDoubleClick;
			using CCustomListBox::setOnRightMouseButtonDown;
			using CCustomListBox::setOnRightMouseButtonUp;
			using CCustomListBox::setOnRightMouseButtonDoubleClick;
			using CCustomListBox::setOnMiddleMouseButtonDown;
			using CCustomListBox::setOnMiddleMouseButtonUp;
			using CCustomListBox::setOnMiddleMouseButtonDoubleClick;
			using CCustomListBox::setOnMouseVerticalWheel;
			using CCustomListBox::setOnMouseHorizontalWheel;
			using CCustomListBox::setOnChangeUseParentFont;
			using CCustomListBox::setOnParentFontChangeName;
			using CCustomListBox::setOnParentFontChangeHeight;
			using CCustomListBox::setOnParentFontChangeWeight;
			using CCustomListBox::setOnParentFontChangeItalic;
			using CCustomListBox::setOnParentFontChangeUnderline;
			using CCustomListBox::setOnParentFontChangeStrikeOut;
			using CCustomListBox::setOnParentFontChangeWidth;
			using CCustomListBox::setOnParentFontChangeCharSet;
			using CCustomListBox::setOnParentFontChangeQuality;
			using CCustomListBox::setOnParentFontChangePitchAndFamily;
			using CCustomListBox::setOnParentFontChangeOrientation;
			using CCustomListBox::setOnParentFontChangeDistance;
			using CCustomListBox::setOnParentFontChangeShadow;
			using CCustomListBox::setOnParentFontChangeShadowShift;
			using CCustomListBox::setOnParentFontChangeShadowBlur;
			using CCustomListBox::setOnParentFontChangeShadowColor;
			using CCustomListBox::setOnParentFontChangeColor;
			using CCustomListBox::setOnParentFontChangeInterpolate;
			using CCustomListBox::setOnParentFontBeginChange;
			using CCustomListBox::setOnParentFontEndChange;
			using CCustomListBox::setOnParentFontChangeSize;
			using CCustomListBox::setOnParentFontChangeStyle;
			using CCustomListBox::setOnFontChangeName;
			using CCustomListBox::setOnFontChangeHeight;
			using CCustomListBox::setOnFontChangeWeight;
			using CCustomListBox::setOnFontChangeItalic;
			using CCustomListBox::setOnFontChangeUnderline;
			using CCustomListBox::setOnFontChangeStrikeOut;
			using CCustomListBox::setOnFontChangeWidth;
			using CCustomListBox::setOnFontChangeCharSet;
			using CCustomListBox::setOnFontChangeQuality;
			using CCustomListBox::setOnFontChangePitchAndFamily;
			using CCustomListBox::setOnFontChangeOrientation;
			using CCustomListBox::setOnFontChangeDistance;
			using CCustomListBox::setOnFontChangeShadow;
			using CCustomListBox::setOnFontChangeShadowShift;
			using CCustomListBox::setOnFontChangeShadowBlur;
			using CCustomListBox::setOnFontChangeShadowColor;
			using CCustomListBox::setOnFontChangeColor;
			using CCustomListBox::setOnFontChangeInterpolate;
			using CCustomListBox::setOnFontBeginChange;
			using CCustomListBox::setOnFontEndChange;
			using CCustomListBox::setOnFontChangeSize;
			using CCustomListBox::setOnFontChangeStyle;
			using CCustomListBox::setOnMouseHover;
			using CCustomListBox::setOnMouseLeave;
			using CCustomListBox::setOnKillFocus;
			using CCustomListBox::setOnSetFocus;
			using CCustomListBox::setOnResetFocus;
			using CCustomListBox::setOnKillCaptureMouse;
			using CCustomListBox::setOnSetCaptureMouse;
			using CCustomListBox::setOnChangeParentStyle;
			using CCustomListBox::setOnChangeStyle;
			using CCustomListBox::setOnShow;
			using CCustomListBox::setOnBeforeHide;
			using CCustomListBox::setOnHide;
			using CCustomListBox::setOnEnable;
			using CCustomListBox::setOnDisable;
			using CCustomListBox::setOnPaint;
			using CCustomListBox::setOnParentResize;
			using CCustomListBox::setOnParentMove;
			using CCustomListBox::setOnBeforeResize;
			using CCustomListBox::setOnResize;
			using CCustomListBox::setOnBeforeMove;
			using CCustomListBox::setOnMove;
			using CCustomListBox::setOnBeforeDetachFromControl;
			using CCustomListBox::setOnDetachFromControl;
			using CCustomListBox::setOnAttachToControl;
			using CCustomListBox::getTabStop;
			using CCustomListBox::getControlStyle;
			using CCustomListBox::getStyle;
			using CCustomListBox::getUseStyle;
			using CCustomListBox::getConstraints;
			using CCustomListBox::getMinConstraints;
			using CCustomListBox::getMaxConstraints;
			using CCustomListBox::getMinWidth;
			using CCustomListBox::getMinHeight;
			using CCustomListBox::getMaxWidth;
			using CCustomListBox::getMaxHeight;
			using CCustomListBox::getControlFont;
			using CCustomListBox::getParentFont;
			using CCustomListBox::getFont;
			using CCustomListBox::getUseParentFont;
			using CCustomListBox::getZIndex;
			using CCustomListBox::setParent;
			using CCustomListBox::setEnabled;
			using CCustomListBox::setVisible;
			using CCustomListBox::setAlign;
			using CCustomListBox::setTabStop;
			using CCustomListBox::setStyle;
			using CCustomListBox::setUseStyle;
			using CCustomListBox::setConstraints;
			using CCustomListBox::setMinConstraints;
			using CCustomListBox::setMinWidth;
			using CCustomListBox::setMinHeight;
			using CCustomListBox::setMaxWidth;
			using CCustomListBox::setMaxHeight;
			using CCustomListBox::setControlFont;
			using CCustomListBox::setFont;
			using CCustomListBox::setUseParentFont;
			using CCustomListBox::setFocus;
			using CCustomListBox::setRect;
			using CCustomListBox::setPosition;
			using CCustomListBox::setLeft;
			using CCustomListBox::setTop;
			using CCustomListBox::setSize;
			using CCustomListBox::setWidth;
			using CCustomListBox::setHeight;
			using CCustomListBox::setTabOrder;
			using CCustomListBox::setCursor;
			using CCustomListBox::setZIndex;

			using CCustomListBox::getState;
			using CCustomListBox::getColumns;
			using CCustomListBox::getBorderWidth;
			using CCustomListBox::getBorderColor;
			using CCustomListBox::getBackgroundColor;
			using CCustomListBox::getBoxShadow;
			using CCustomListBox::getBoxShadowShift;
			using CCustomListBox::getBoxShadowShiftX;
			using CCustomListBox::getBoxShadowShiftY;
			using CCustomListBox::getBoxShadowRadius;
			using CCustomListBox::getBoxShadowColor;
			using CCustomListBox::getPadding;
			using CCustomListBox::getPaddingLeft;
			using CCustomListBox::getPaddingTop;
			using CCustomListBox::getPaddingRight;
			using CCustomListBox::getPaddingBottom;
			using CCustomListBox::getVerticalScrollBar;
			using CCustomListBox::getHorizontalScrollBar;
			using CCustomListBox::getItemCount;
			using CCustomListBox::getActiveItemIndex;
			using CCustomListBox::getResetSearchInterval;
			using CCustomListBox::getAllowMultiSelect;
			using CCustomListBox::getAllowSearch;
			using CCustomListBox::setColumns;
			using CCustomListBox::setBorderWidth;
			using CCustomListBox::setBorderColor;
			using CCustomListBox::setBackgroundColor;
			using CCustomListBox::setBoxShadow;
			using CCustomListBox::setBoxShadowShift;
			using CCustomListBox::setBoxShadowShiftX;
			using CCustomListBox::setBoxShadowShiftY;
			using CCustomListBox::setBoxShadowRadius;
			using CCustomListBox::setBoxShadowColor;
			using CCustomListBox::setPadding;
			using CCustomListBox::setPaddingLeft;
			using CCustomListBox::setPaddingTop;
			using CCustomListBox::setPaddingRight;
			using CCustomListBox::setPaddingBottom;
			using CCustomListBox::setVerticalScrollBar;
			using CCustomListBox::setHorizontalScrollBar;
			using CCustomListBox::setActiveItemIndex;
			using CCustomListBox::setResetSearchInterval;
			using CCustomListBox::setAllowMultiSelect;
			using CCustomListBox::setAllowSearch;
			using CCustomListBox::Delete;
			using CCustomListBox::DeleteAll;
			using CCustomListBox::DeleteSelected;
			using CCustomListBox::DeleteUnselected;
			using CCustomListBox::SelectAll;
			using CCustomListBox::DeselectAll;
			using CCustomListBox::InvertSelection;
			using CCustomListBox::SelectRange;
		};
	}
}