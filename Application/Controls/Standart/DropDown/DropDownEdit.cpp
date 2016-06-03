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
		CDropDown::CDropDownEdit::CDropDownEdit(CDropDown *parent) :CEdit()
		{
			m_sClassName = L"CDropDown.Edit";
			m_bAcceptForm = false;
			m_eAlign = alClient;
			for (int i = 0; i <= stDisabledHovered; i++)
			{
				m_sBlock[i].BorderWidth = { 0, 0, 0, 0 };
				m_sBlock[i].Padding = { 0, 0, 0, 0 };
				m_sBlock[i].BackgroundColor = { 0, 0, 0, 0 };
			}
			setParent(parent);
		}
	#pragma endregion

	#pragma region Notifications
		bool CDropDown::CDropDownEdit::NotifyOnKeyDown(const IWindow::KEY key)
		{
			CEdit::NotifyOnKeyDown(key);
			if (key == IWindow::keyUp)
				(dynamic_cast<CDropDown*>(getParent()))->NotifyOnEditKeyUp();
			else if (key == IWindow::keyDown)
				(dynamic_cast<CDropDown*>(getParent()))->NotifyOnEditKeyDown();
			else if (key == IWindow::keyF4)
				(dynamic_cast<CDropDown*>(getParent()))->NotifyOnEditKeyF4();
			return false;
		}

		void CDropDown::CDropDownEdit::NotifyOnChange()
		{
			CEdit::NotifyOnChange();
			(dynamic_cast<CDropDown*>(getParent()))->NotifyOnEditChange();
		}

		void CDropDown::CDropDownEdit::NotifyOnMouseHover()
		{
			CEdit::NotifyOnMouseHover();
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownEdit::NotifyOnMouseLeave()
		{
			CEdit::NotifyOnMouseLeave();
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownEdit::NotifyOnKillFocus()
		{
			CEdit::NotifyOnKillFocus();
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownEdit::NotifyOnSetFocus(CControl *old)
		{
			CEdit::NotifyOnSetFocus(old);
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownEdit::NotifyOnResetFocus()
		{
			CEdit::NotifyOnResetFocus();
			getParent()->Repaint(true);
		}

		void CDropDown::CDropDownEdit::NotifyOnBeforeHide()
		{
			CEdit::NotifyOnBeforeHide();
			getParent()->Repaint(true);
		}
	#pragma endregion

	#pragma region Getters
		CDropDown::CDropDownEdit::STATE CDropDown::CDropDownEdit::getState()
		{
			CDropDown *dd{ dynamic_cast<CDropDown*>(getParent()) };
			CDropDownListBox *listbox{ dd->getListBox() };
			if (!dd->m_bEnabled)
				return stDisabled;
			if (m_pForm)
			{
				if (m_pForm->getActiveControl() == this || m_pForm->getActiveControl() == dd || m_pForm->getActiveControl() == listbox)
					return stActive;
				if (m_pForm->getHoveredControl() == this || m_pForm->getHoveredControl() == dd || m_pForm->getHoveredControl() == listbox || m_pForm->getHoveredControl() == listbox->getHScrollBar() || m_pForm->getHoveredControl() == listbox->getVScrollBar())
					return stNormalHovered;
			}
			return stNormal;
		}
	#pragma endregion
	}
}