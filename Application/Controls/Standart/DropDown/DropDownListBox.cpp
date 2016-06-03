// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "DropDown.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructor
		CDropDown::CDropDownListBox::CDropDownListBox(CDropDown *parent) :CListBox()
		{
			m_sClassName = L"CDropDown.ListBox";
			m_bVisible = false;
			m_bAcceptForm = false;
			m_sConstraints = { 20, 20, 0, 130 };
			m_bBoxShadow = true;
			m_sBoxShadowShift = { 2, 2 };
			m_iBoxShadowRadius = 3;
			m_aBoxShadowColor[stNormal] = { 152, 152, 152, 200 };
			m_aBoxShadowColor[stActive] = { 152, 152, 152, 200 };
			m_aBoxShadowColor[stHovered] = { 152, 152, 152, 200 };
			m_aBoxShadowColor[stDisabled] = { 152, 152, 152, 200 };
			m_bAllowMultiSelect = false;
			setParent(parent);
		}
	#pragma endregion

	#pragma region Helpers
		void CDropDown::CDropDownListBox::StartCapture() // Just remove CaptureMouse() because it called when control is showing
		{
			m_bMouseDown = true;
		}

		void CDropDown::CDropDownListBox::EndCapture() // Just remove ReleaseCaptureMouse() because control capture mouse all time when visible(except when child scrollbars capture mouse)
		{
			m_bMouseDown = false;
		}
	#pragma endregion

	#pragma region Notifications
		bool CDropDown::CDropDownListBox::NotifyOnKeyDown(const IWindow::KEY key)
		{
			CListBox::NotifyOnKeyDown(key);
			switch (key)
			{
			case IWindow::keyF4:
			case IWindow::keyEscape:
				(dynamic_cast<CDropDown*>(getParent()))->NotifyOnEditKeyF4();
				break;
			}
			return false;
		}

		bool CDropDown::CDropDownListBox::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (CListBox::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift))
				if (m_pForm->getHoveredControl() != getParent())
				{
					setVisible(false);
					getParent()->Repaint(true);
				}
			return false;
		}

		void CDropDown::CDropDownListBox::NotifyOnShow()
		{
			CListBox::NotifyOnShow();
			m_pForm->CaptureMouse(this);
		}

		void CDropDown::CDropDownListBox::NotifyOnMouseHover()
		{
			CListBox::NotifyOnMouseHover();
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownListBox::NotifyOnMouseLeave()
		{
			CListBox::NotifyOnMouseLeave();
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownListBox::NotifyOnKillFocus()
		{
			CListBox::NotifyOnKillFocus();
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownListBox::NotifyOnSetFocus(CControl *old)
		{
			CListBox::NotifyOnSetFocus(old);
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownListBox::NotifyOnResetFocus()
		{
			CListBox::NotifyOnResetFocus();
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownListBox::NotifyOnBeforeHide()
		{
			CListBox::NotifyOnBeforeHide();
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownListBox::NotifyOnClickItem(CListBoxItem *item)
		{
			dynamic_cast<CDropDown*>(getParent())->NotifyOnClickItem(item);
		}
	#pragma endregion

	#pragma region Getters
		CCustomListBox::STATE CDropDown::CDropDownListBox::getState()
		{
			CDropDown *dd{ dynamic_cast<CDropDown*>(getParent()) };
			CDropDownEdit *edit{ dd->getEdit() };
			if (!dd->m_bEnabled)
				return stDisabled;
			if (m_pForm)
			{
				if (m_pForm->getActiveControl() == this || m_pForm->getActiveControl() == dd || m_pForm->getActiveControl() == edit)
					return stActive;
				if (m_pForm->getHoveredControl() == this || m_pForm->getHoveredControl() == dd || m_pForm->getHoveredControl() == edit || m_pForm->getHoveredControl() == getHScrollBar() || m_pForm->getHoveredControl() == getVScrollBar())
					return stHovered;
			}
			return stNormal;
		}

		APP_RECT CDropDown::CDropDownListBox::getVisibleRect()
		{
			return ClientToForm(getRect());
		}

		CCustomListBox *CDropDown::CDropDownListBox::setActiveItemIndex(int value)
		{
			if (value != m_iActiveItemIndex)
			{
				if (m_pForm)
					m_pForm->LockRepaint();
				if (getActiveItem())
					getActiveItem()->setSelected(false);
				CListBox::setActiveItemIndex(value);
				if (getActiveItem())
					getActiveItem()->setSelected(true);
				if (m_pForm)
					m_pForm->UnlockRepaint();
			}
			return this;
		}
	#pragma endregion
	}
}