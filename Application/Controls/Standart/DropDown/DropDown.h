// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#pragma once

#include "..\..\..\Control.h"
#include "..\Edit\Edit.h"
#include "..\ListBox\ListBox.h"

namespace licui
{
	namespace application
	{
		class CDropDown :public CControl
		{
		private:
			class CDropDownEdit;
			class CDropDownListBox;

			friend CDropDownEdit;
			friend CDropDownListBox;
		public:
			enum STATE
			{
				stNormal,
				stActive,
				stHovered,
				stArrowHovered, // Just for settings. getState() never return this value
				stOpened,
				stDisabled
			};
			enum ARROW_ALIGN
			{
				aalLeft,
				aalRight
			};
		private:
			class CDropDownEdit :public CEdit
			{
				friend CDropDownListBox;
			protected:
				bool NotifyOnKeyDown(const IWindow::KEY key) override;
				void NotifyOnChange() override;
				void NotifyOnMouseHover() override;
				void NotifyOnMouseLeave() override;
				void NotifyOnKillFocus() override;
				void NotifyOnSetFocus(CControl *old) override;
				void NotifyOnResetFocus() override;
				void NotifyOnBeforeHide() override;
			public:
				STATE getState() override;

				CDropDownEdit(CDropDown *parent);
			};

			class CDropDownListBox :public CListBox
			{
				friend CDropDownEdit;
				friend CDropDown;
			protected:
				void StartCapture() override;
				void EndCapture() override;

				bool NotifyOnKeyDown(const IWindow::KEY key) override;
				bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;

				void NotifyOnShow() override;
				void NotifyOnMouseHover() override;
				void NotifyOnMouseLeave() override;
				void NotifyOnKillFocus() override;
				void NotifyOnSetFocus(CControl *old) override;
				void NotifyOnResetFocus() override;
				void NotifyOnBeforeHide() override;

				void NotifyOnClickItem(CListBoxItem *item) override;
			public:
				STATE getState() override;
				APP_RECT getVisibleRect() override;
				CCustomListBox *setActiveItemIndex(int value) override;

				CDropDownListBox(CDropDown *parent);
			};

			struct STYLE :public IImage::GRADIENT
			{
				APP_COLOR BorderColor;
				APP_COLOR BackgroundColor;
				APP_COLOR Text; // Used only for non-editable dropdown
				APP_COLOR Shadow; // Used only for non-editable dropdown
			};
		private:
			bool m_bEditable;
			math::RECTANGLE<size_t> m_sPadding;
			math::RECTANGLE<size_t> m_sBorderWidth;
			math::RECTANGLE<size_t> m_sBorderRadius;
			size_t m_iBorderAntiAliazing;
			STYLE m_aStyle[stDisabled + 1][2];
			ARROW_ALIGN m_eArrowAlign;
			STYLE m_aArrowStyle[stDisabled + 1][2];
			math::RECTANGLE<size_t> m_sArrowPadding;
			math::RECTANGLE<size_t> m_sArrowBorderWidth;
			math::RECTANGLE<size_t> m_sArrowBorderRadius;
			size_t m_iArrowBorderAntiAliazing;

			bool m_bArrowHovered;

			CDropDownEdit *getEdit();
			CDropDownListBox *getListBox();

			String getStateName(const STATE state);
			void FillStyles();
			void ToggleListBox();
			void ActivateNextItem();
			void ActivatePrevItem();
			APP_RECT CalculateArrowRect();
			bool SearchArrowImage(APP_IMAGE **image, APP_RECT &rect, const bool ignore_state);

			void ProcessKeyUp();
			void ProcessKeyDown();

			void PaintBackground(APP_RECT clip);
			void PaintArrow(APP_RECT clip);
			void PaintText(APP_RECT clip);
		protected:
			bool UpdateFromStyle() override;

			bool NotifyOnKeyDown(const IWindow::KEY key) override;
			bool NotifyOnMouseMove(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;
			bool NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift) override;

			void NotifyOnKillFocus() override;
			void NotifyOnSetFocus(CControl *old) override;
			void NotifyOnResetFocus() override;
			void NotifyOnMouseHover() override;
			void NotifyOnMouseLeave() override;
			void NotifyOnPaint(APP_RECT clip) override;

			virtual void NotifyOnClickItem(CListBoxItem *item);
			virtual void NotifyOnEditKeyDown();
			virtual void NotifyOnEditKeyUp();
			virtual void NotifyOnEditKeyF4();
			virtual void NotifyOnEditChange();
		public:
			APP_RECT getClientRect() override;

			virtual STATE getState();
			virtual bool getEditable() const;
			virtual String getText();
			virtual int getActiveItemIndex();
			virtual size_t getItemCount();
			virtual String getItem(const size_t index);

			virtual CDropDown *setEditable(const bool value);
			virtual CDropDown *setText(const String &value);
			virtual CDropDown *setActiveItemIndex(int value);
			virtual CDropDown *setItem(const size_t index, const String &value);

			CDropDown();
			CDropDown(CForm *form);
			CDropDown(CControl *parent);
			~CDropDown();

			CDropDown *AddItem(const String &name);
			CDropDown *DeleteItem(const size_t index);
			CDropDown *DeleteItems();
		public:
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
			using CControl::setRect;
			using CControl::setPosition;
			using CControl::setLeft;
			using CControl::setTop;
			using CControl::setSize;
			using CControl::setWidth;
			using CControl::setHeight;
			using CControl::setTabOrder;
			using CControl::setZIndex;
		};
	}
}