// Copyright © 2016 BugsEx. All rights reserved.
// Author: Dmitriy Lysenko
// License: http://opensource.org/licenses/MIT
// Site: http://lic-ui.bugsex.net

#include "MainMenu.h"
#include "..\..\..\Presenter.h"
#include "..\..\..\Style.h"

namespace licui
{
	namespace application
	{
	#pragma region Constructors
		CMainMenu::CMainMenu() :
			CControl(),
			m_iActiveMenuItemIndex{ -1 },
			m_pImageList{ nullptr },
			m_sBackgroundColor{ 230, 230, 230, 255 },
			m_fOnClick{ nullptr },
			m_bDeactivating{ false },
			m_bActivating{ false },
			m_bCaretVisible{ false }
		{
			m_sClassName = L"CMainMenu";
			m_bAcceptForm = true;
			m_eAlign = alTop;
		}

		CMainMenu::CMainMenu(CForm *form) :CMainMenu()
		{
			setForm(form);
		}
	#pragma endregion

	#pragma region Getters
		bool CMainMenu::getIsActive() const
		{
			return m_pForm && m_pForm->getCaptureKeyboardControl() == this;
		}

		CImageList *CMainMenu::getImageList()
		{
			return m_pImageList;
		}

		int CMainMenu::getActiveMenuItemIndex()
		{
			return m_iActiveMenuItemIndex;
		}

		CMainMenuItem *CMainMenu::getActiveMenuItem()
		{
			return dynamic_cast<CMainMenuItem*>(getControl(m_iActiveMenuItemIndex));
		}

		size_t CMainMenu::getMenuItemCount()
		{
			return getControlCount();
		}

		CMainMenuItem *CMainMenu::getMenuItem(const int index)
		{
			return dynamic_cast<CMainMenuItem*>(getControl(index));
		}

		APP_COLOR CMainMenu::getBackgroundColor() const
		{
			return m_sBackgroundColor;
		}

		CMenuItem::FOnClick CMainMenu::getOnClick() const
		{
			return m_fOnClick;
		}
	#pragma endregion

	#pragma region Setters
		CMainMenu *CMainMenu::setImageList(CImageList *value)
		{
			if (value != m_pImageList)
			{
				m_pImageList = value;
				Update();
			}
			return this;
		}

		CMainMenu *CMainMenu::setActiveMenuItemIndex(int value)
		{
			if (value < -1 || value >= (int)getControlCount())
				value = -1;
			if (getIsActive() && value != m_iActiveMenuItemIndex)
			{
				m_pForm->LockRepaint();
				bool visible{ getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible };
				if (visible)
					getActiveMenuItem()->getMenu()->Hide();
				if (getMenuItem(value)->m_bEnabled)
				{
					if (getActiveMenuItem())
						getActiveMenuItem()->Repaint(false);
					m_iActiveMenuItemIndex = value;
					getActiveMenuItem()->Repaint(false);
					if (visible && getActiveMenuItem()->getMenu())
						getActiveMenuItem()->getMenu()->Show(getActiveMenuItem()->m_sMenuShift.X, getActiveMenuItem()->getHeight() + getActiveMenuItem()->m_sMenuShift.Y);
				}
				else
				{
					m_iActiveMenuItemIndex = -1;
					Deactivate();
				}
				m_pForm->UnlockRepaint();
			}
			return this;
		}

		CMainMenu *CMainMenu::setActiveMenuItem(CMainMenuItem *value)
		{
			if (getIsActive() && value != getActiveMenuItem())
			{
				if (!value)
					Deactivate();
				else
					for (size_t index = 0; index < getMenuItemCount(); index++)
						if (getMenuItem(index) == value)
						{
							setActiveMenuItemIndex(index);
							break;
						}
			}
			return this;
		}

		CMainMenu *CMainMenu::setBackgroundColor(const APP_COLOR &value)
		{
			if (value != m_sBackgroundColor)
			{
				m_sBackgroundColor = value;
				Repaint(false);
			}
			return this;
		}

		CMainMenu *CMainMenu::setOnClick(CMenuItem::FOnClick value)
		{
			m_fOnClick = value;
			return this;
		}
	#pragma endregion

	#pragma region Notifications
		void CMainMenu::NotifyOnBeforeDetachComponentFromForm(CComponent *component)
		{
			if (component == m_pImageList)
			{
				m_pImageList = nullptr;
				Update();
			}
			CControl::NotifyOnBeforeDetachComponentFromForm(component);
		}

		void CMainMenu::NotifyOnUpdateComponent(CComponent *component)
		{
			if (component == m_pImageList)
				Update();
			CControl::NotifyOnUpdateComponent(component);
		}

		bool CMainMenu::NotifyOnKeyDown(const IWindow::KEY key)
		{
			switch (key)
			{
			case IWindow::keyUp:
				ProcessKeyUp();
				break;
			case IWindow::keyDown:
				ProcessKeyDown();
				break;
			case IWindow::keyLeft:
				ProcessKeyLeft();
				break;
			case IWindow::keyRight:
				ProcessKeyRight();
				break;
			case IWindow::keyHome:
				ProcessKeyHome();
				break;
			case IWindow::keyEnd:
				ProcessKeyEnd();
				break;
			case IWindow::keySpace:
				ProcessKeySpace();
				break;
			case IWindow::keyReturn:
				ProcessKeyEnter();
				break;
			case IWindow::keyEscape:
				ProcessKeyEscape();
				break;
			case IWindow::keyTab:
				ProcessKeyTab();
				break;
			}
			CControl::NotifyOnKeyDown(key);
			return true;
		}

		bool CMainMenu::NotifyOnKeyUp(const IWindow::KEY key)
		{
			CControl::NotifyOnKeyUp(key);
			return true;
		}

		bool CMainMenu::NotifyOnChar(const wchar_t chr)
		{
			CControl::NotifyOnChar(chr);
			return true;
		}

		bool CMainMenu::NotifyOnDeadChar(const wchar_t chr)
		{
			CControl::NotifyOnDeadChar(chr);
			return true;
		}

		bool CMainMenu::NotifyOnSysKeyDown(const IWindow::KEY key)
		{
			CControl::NotifyOnSysKeyDown(key);
			return true;
		}

		bool CMainMenu::NotifyOnSysKeyUp(const IWindow::KEY key)
		{
			CControl::NotifyOnSysKeyUp(key);
			return true;
		}

		bool CMainMenu::NotifyOnSysChar(const wchar_t chr)
		{
			CControl::NotifyOnSysChar(chr);
			return true;
		}

		bool CMainMenu::NotifyOnSysDeadChar(const wchar_t chr)
		{
			CControl::NotifyOnSysDeadChar(chr);
			return true;
		}

		bool CMainMenu::NotifyOnLeftMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (!HitTest(x, y))
				Deactivate();
			CControl::NotifyOnLeftMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return false;
		}

		bool CMainMenu::NotifyOnLeftMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu())
				getActiveMenuItem()->getMenu()->ProcessMouseUp();
			if (!HitTest(x, y))
				Deactivate();
			CControl::NotifyOnLeftMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return false;
		}

		bool CMainMenu::NotifyOnLeftMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CControl::NotifyOnLeftMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMainMenu::NotifyOnRightMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			bool test{ HitTest(x, y) };
			if (!test)
				Deactivate();
			CControl::NotifyOnRightMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return test;
		}

		bool CMainMenu::NotifyOnRightMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			bool test{ HitTest(x, y) };
			if (!test)
				Deactivate();
			CControl::NotifyOnRightMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return test;
		}

		bool CMainMenu::NotifyOnRightMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CControl::NotifyOnRightMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMainMenu::NotifyOnMiddleMouseButtonDown(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			bool test{ HitTest(x, y) };
			if (!test)
				Deactivate();
			CControl::NotifyOnMiddleMouseButtonDown(x, y, ctrl, left, middle, right, shift);
			return test;
		}

		bool CMainMenu::NotifyOnMiddleMouseButtonUp(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			bool test{ HitTest(x, y) };
			if (!test)
				Deactivate();
			CControl::NotifyOnMiddleMouseButtonUp(x, y, ctrl, left, middle, right, shift);
			return test;
		}

		bool CMainMenu::NotifyOnMiddleMouseButtonDoubleClick(const int x, const int y, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CControl::NotifyOnMiddleMouseButtonDoubleClick(x, y, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMainMenu::NotifyOnMouseVerticalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				getActiveMenuItem()->getMenu()->ProcessMouseWheel(x, y, delta);
			CControl::NotifyOnMouseVerticalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		bool CMainMenu::NotifyOnMouseHorizontalWheel(const int x, const int y, const int delta, const bool ctrl, const bool left, const bool middle, const bool right, const bool shift)
		{
			CControl::NotifyOnMouseHorizontalWheel(x, y, delta, ctrl, left, middle, right, shift);
			return true;
		}

		void CMainMenu::NotifyOnKillCaptureKeyboard()
		{
			Deactivate();
			CControl::NotifyOnKillCaptureKeyboard();
		}

		void CMainMenu::NotifyOnKillCaptureMouse()
		{
			Deactivate();
			m_pForm->getWindow()->ReleaseMouseCapture();
			CControl::NotifyOnKillCaptureMouse();
		}

		void CMainMenu::NotifyOnSetCaptureMouse()
		{
			m_pForm->getWindow()->CaptureMouse();
			CControl::NotifyOnSetCaptureMouse();
		}

		void CMainMenu::NotifyOnShow()
		{
			CControl::NotifyOnShow();
			Update();
		}

		void CMainMenu::NotifyOnDetachControl(CControl *control)
		{
			CControl::NotifyOnDetachControl(control);
			if (getActiveMenuItem() == control)
				Deactivate();
			else
				Update();
		}

		void CMainMenu::NotifyOnPaint(APP_RECT clip)
		{
			m_pForm->getPresenter()->FillRect(m_sBackgroundColor, clip, ClientToForm(getRect()), ClientToForm(getRect()), { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, graphics::bplInside, nullptr, nullptr, true);
			CControl::NotifyOnPaint(clip);
		}

		void CMainMenu::NotifyOnClick(CControl *sender)
		{
			if (m_fOnClick)
				m_fOnClick(sender, getCallbackParam());
		}
	#pragma endregion

	#pragma region Helpers
		void CMainMenu::Update()
		{
			if (!getVisibleWithParents() || !m_pForm)
				return;
			size_t height{ 0 }, width_left{ 0 }, width_right{ 0 };
			for (size_t i = 0; i < getMenuItemCount(); i++)
			{
				math::POINT<size_t> size = getMenuItem(i)->CalculateSize();
				height = std::max(height, size.Y);
				if (getMenuItem(i)->m_eAlign == CMainMenuItem::ialLeft)
					width_left += size.X;
				else
					width_right += size.X;
			}
			m_sInitialRect.Right = m_sInitialRect.Left + width_left + width_right;
			m_sInitialRect.Bottom = m_sInitialRect.Top + height;
			m_pForm->LockRepaint();
			UpdateRect();
			UpdateControls(width_right);
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				getActiveMenuItem()->getMenu()->Show(getActiveMenuItem()->m_sMenuShift.X, getActiveMenuItem()->getHeight() + getActiveMenuItem()->m_sMenuShift.Y);
			m_pForm->UpdateHoveredControl();
			m_pForm->UnlockRepaint();
		}

		void CMainMenu::UpdateControls(size_t width_right)
		{
			int x_left{ 0 }, x_right{ getWidth() - (int)width_right };
			for (size_t i = 0; i < getMenuItemCount(); i++)
			{
				math::POINT<size_t> size = getMenuItem(i)->CalculateSize();
				if (getMenuItem(i)->m_eAlign == CMainMenuItem::ialLeft)
				{
					getMenuItem(i)->setRect({ x_left, 0, x_left + (int)size.X, getHeight() });
					x_left += size.X;
				}
				else
				{
					getMenuItem(i)->setRect({ x_right, 0, x_right + (int)size.X, getHeight() });
					x_right += size.X;
				}
			}
		}

		bool CMainMenu::HitTest(const int x, const int y)
		{
			bool result{ false };
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				result = getActiveMenuItem()->getMenu()->HitTest(x, y);
			if (!result)
			{
				APP_RECT r = ClientToForm(getRect());
				if (x >= r.Left && x < r.Right && y >= r.Top && y < r.Bottom)
					result = true;
			}
			return result;
		}

		bool CMainMenu::UpdateFromStyle()
		{
			if (!getStyle())
				return false;
			m_sBackgroundColor = getStyle()->getParameterByName(m_sClassName + L".BackgroundColor", m_sBackgroundColor);
			return true;
		}

		CMainMenu *CMainMenu::Activate()
		{
			if (!m_bActivating && !getIsActive() && m_pForm && m_bVisible)
			{
				m_bActivating = true;
				m_bCaretVisible = m_pForm->getWindow()->IsCaretVisible();
				m_pForm->getWindow()->HideCaret();
				m_pForm->LockRepaint();
				m_pForm->CaptureKeyboard(this);
				m_pForm->CaptureMouse(this);
				if (!getActiveMenuItem())
					ProcessKeyTab();
				Repaint(false);
				m_pForm->UnlockRepaint();
				m_bActivating = false;
			}
			return this;
		}

		CMainMenu *CMainMenu::Deactivate()
		{
			if (!m_bDeactivating && m_pForm)
			{
				m_bDeactivating = true;
				m_pForm->LockRepaint();
				if (getActiveMenuItem() && getActiveMenuItem()->getMenu())
					getActiveMenuItem()->getMenu()->Hide();
				m_iActiveMenuItemIndex = -1;
				if (m_pForm->getCaptureKeyboardControl() == this)
					m_pForm->ReleaseCaptureKeyboard();
				if (m_pForm->getCaptureMouseControl() == this)
					m_pForm->ReleaseCaptureMouse();
				m_pForm->UpdateHoveredControl();
				if (m_bCaretVisible)
					m_pForm->getWindow()->ShowCaret();
				Repaint(true);
				m_pForm->UnlockRepaint();
				m_bDeactivating = false;
			}
			return this;
		}
	#pragma endregion

	#pragma region Menu items
		CMainMenu *CMainMenu::AddMenuItem(CMainMenuItem *item)
		{
			if (item && item->getMainMenu() != this)
				item->setMainMenu(this);
			return this;
		}

		CMainMenu *CMainMenu::DeleteMenuItem(const size_t index)
		{
			DeleteControl(index);
			return this;
		}

		CMainMenu *CMainMenu::DeleteMenuItem(CMainMenuItem *item)
		{
			DeleteControl(item);
			return this;
		}

		CMainMenu *CMainMenu::DeleteMenuItems()
		{
			DeleteControls();
			return this;
		}
	#pragma endregion

	#pragma region Process keys
		void CMainMenu::ProcessKeyLeft()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
			{
				getActiveMenuItem()->getMenu()->ProcessKeyLeft();
				return;
			}
			int index{ m_iActiveMenuItemIndex - 1 };
			while (index >= 0 && getMenuItem(index) && !getMenuItem(index)->m_bEnabled)
				index--;
			if (!getMenuItem(index) || !getMenuItem(index)->m_bEnabled)
			{
				index = getMenuItemCount() - 1;
				while (index > m_iActiveMenuItemIndex && !getMenuItem(index)->m_bEnabled)
					index--;
			}
			if (getMenuItem(index) && getMenuItem(index)->m_bEnabled)
				setActiveMenuItemIndex(index);
		}

		void CMainMenu::ProcessKeyRight()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
			{
				getActiveMenuItem()->getMenu()->ProcessKeyRight();
				return;
			}
			int index{ m_iActiveMenuItemIndex + 1 };
			while (index < (int)getMenuItemCount() && getMenuItem(index) && !getMenuItem(index)->m_bEnabled)
				index++;
			if (!getMenuItem(index) || !getMenuItem(index)->m_bEnabled)
			{
				index = 0;
				while (index < m_iActiveMenuItemIndex && !getMenuItem(index)->m_bEnabled)
					index++;
			}
			if (getMenuItem(index) && getMenuItem(index)->m_bEnabled)
				setActiveMenuItemIndex(index);
		}

		void CMainMenu::ProcessKeyHome()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
			{
				getActiveMenuItem()->getMenu()->ProcessKeyHome();
				return;
			}
			int index{ 0 };
			while (index < (int)getMenuItemCount() && !getMenuItem(index)->m_bEnabled)
				index++;
			if (getMenuItem(index) && getMenuItem(index)->m_bEnabled)
				setActiveMenuItemIndex(index);
		}

		void CMainMenu::ProcessKeyEnd()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
			{
				getActiveMenuItem()->getMenu()->ProcessKeyEnd();
				return;
			}
			int index{ (int)getMenuItemCount() - 1 };
			while (index >= 0 && !getMenuItem(index)->m_bEnabled)
				index--;
			if (getMenuItem(index) && getMenuItem(index)->m_bEnabled)
				setActiveMenuItemIndex(index);
		}

		void CMainMenu::ProcessKeyUp()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu())
				if (getActiveMenuItem()->getMenu()->m_bVisible)
					getActiveMenuItem()->getMenu()->ProcessKeyUp();
				else
				{
					getActiveMenuItem()->getMenu()->Show(getActiveMenuItem()->m_sMenuShift.X, getActiveMenuItem()->getHeight() + getActiveMenuItem()->m_sMenuShift.Y);
					getActiveMenuItem()->getMenu()->ProcessKeyUp();
				}
		}

		void CMainMenu::ProcessKeyDown()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu())
				if (getActiveMenuItem()->getMenu()->m_bVisible)
					getActiveMenuItem()->getMenu()->ProcessKeyDown();
				else
				{
					getActiveMenuItem()->getMenu()->Show(getActiveMenuItem()->m_sMenuShift.X, getActiveMenuItem()->getHeight() + getActiveMenuItem()->m_sMenuShift.Y);
					getActiveMenuItem()->getMenu()->ProcessKeyDown();
				}
		}

		void CMainMenu::ProcessKeyEnter()
		{
			CMainMenuItem *item{ getActiveMenuItem() };
			if (item && item->getMenu() && item->getMenu()->m_bVisible)
			{
				item->getMenu()->ProcessKeyEnter();
				return;
			}
			if (item)
			{
				if (item->getMenu())
					item->getMenu()->Show(item->m_sMenuShift.X, item->getHeight() + item->m_sMenuShift.Y);
				else
				{
					
					Deactivate();
					item->NotifyOnClick();
				}
			}
		}

		void CMainMenu::ProcessKeySpace()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
				getActiveMenuItem()->getMenu()->ProcessKeySpace();
		}

		void CMainMenu::ProcessKeyEscape()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
			{
				getActiveMenuItem()->getMenu()->ProcessKeyEscape();
				return;
			}
			Deactivate();
		}

		void CMainMenu::ProcessKeyTab()
		{
			if (getActiveMenuItem() && getActiveMenuItem()->getMenu() && getActiveMenuItem()->getMenu()->m_bVisible)
			{
				getActiveMenuItem()->getMenu()->ProcessKeyTab();
				return;
			}
			ProcessKeyRight();
		}
	#pragma endregion
	}
}